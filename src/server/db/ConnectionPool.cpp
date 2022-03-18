#include "server/db/ConnectionPool.h"
using std::placeholders::_1;

ConnectionPool::ConnectionPool()
    : min_connection_(MIN_CONNECTION), max_connection_(MAX_CONNECTION),
      now_conn_count_(MIN_CONNECTION), pool_alive_(true),
      release_thread_(thread(&ConnectionPool::ReleaseConnection, this)) {
    lock_guard<mutex> lg(mtx_);
    for (int i = 0; i < min_connection_; ++i) {
        MySQLDB *mysql = new MySQLDB;
        pool_.push_back(mysql);
    }
}

unique_ptr<MySQLDB, retconnfunc> ConnectionPool::GetConnction() {
    unique_lock<mutex> lock(mtx_);
    if (!pool_.empty()) {
        MySQLDB *mysql = pool_.front();
        pool_.pop_front();
        return unique_ptr<MySQLDB, retconnfunc>(
            mysql, std::bind(&ConnectionPool::ReturnConnection, this, _1));
    }

    if (now_conn_count_ < max_connection_) {
        ++now_conn_count_;
        return unique_ptr<MySQLDB, retconnfunc>(
            new MySQLDB,
            std::bind(&ConnectionPool::ReturnConnection, this, _1));
    }

    if (cv_.wait_for(lock, chrono::seconds(2),
                     [this]() { return !pool_.empty(); })) {
        MySQLDB *mysql = pool_.front();
        pool_.pop_front();
        return unique_ptr<MySQLDB, retconnfunc>(
            mysql, std::bind(&ConnectionPool::ReturnConnection, this, _1));
    }
    // 超时
    // cout << "超时" << endl;
    return nullptr;
}

void ConnectionPool::ReturnConnection(MySQLDB *mysql) {
    if (mysql != nullptr) {
        unique_lock<mutex> lock(mtx_);
        pool_.push_back(mysql);
        mysql->ResetLastTime();
        cv_.notify_one();
    }
}

ConnectionPool::~ConnectionPool() {
    pool_alive_ = false;
    release_thread_.join();
    unique_lock<mutex> lock(mtx_);
    while (!pool_.empty()) {
        MySQLDB *mysql = pool_.front();
        delete mysql;
        pool_.pop_front();
    }
}

void ConnectionPool::ReleaseConnection() {
    while (pool_alive_) {
        this_thread::sleep_for(chrono::seconds(MAX_LIVE_TIME / 10));
        lock_guard<mutex> lg(mtx_);
        time_t now = time(nullptr);
        for (auto iter = pool_.begin();
             iter != pool_.end() && now_conn_count_ >= min_connection_;
             ++iter) {
            if (difftime(now, (*iter)->GetLastTime()) >= MAX_LIVE_TIME) {
                MySQLDB *mysql = *iter;
                delete mysql;
                --now_conn_count_;
                iter = pool_.erase(iter);
            }
        }
    }
}