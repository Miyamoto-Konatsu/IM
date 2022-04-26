#include "server/db/ConnectionPool.h"
using std::placeholders::_1;

ConnectionPool::ConnectionPool()
    : min_connection_(MIN_CONNECTION), max_connection_(MAX_CONNECTION),
      now_conn_count_(MIN_CONNECTION), pool_alive_(true),
      release_thread_(thread(&ConnectionPool::ReleaseConnection, this)) {
    lock_guard<mutex> lg(mtx_);
    for (int i = 0; i < min_connection_; ++i) {
        MySQLDB *mysql = new MySQLDB;
        pool_.push(mysql);
    }
}

unique_ptr<MySQLDB, retconnfunc> ConnectionPool::GetConnction() {
    unique_lock<mutex> lock(mtx_);
    if (!pool_.empty()) {
        MySQLDB *mysql = pool_.front();
        pool_.pop();
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
        pool_.pop();
        return unique_ptr<MySQLDB, retconnfunc>(
            mysql, std::bind(&ConnectionPool::ReturnConnection, this, _1));
    }
    return nullptr;
}

void ConnectionPool::ReturnConnection(MySQLDB *mysql) {
    if (mysql != nullptr) {
        unique_lock<mutex> lock(mtx_);
        pool_.push(mysql);
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
        pool_.pop();
        delete mysql;
        --now_conn_count_;
    }
}

void ConnectionPool::ReleaseConnection() {
    while (pool_alive_) {
        int sleep_time = MAX_LIVE_TIME;
        {
            lock_guard<mutex> lg(mtx_);
            time_t now = time(nullptr);
            //连接池中有未使用的连接，而且使用+未使用的连接数大于最小连接数时
            //可以释放池中中超时的连接
            while (!pool_.empty() && now_conn_count_ > min_connection_) {
                MySQLDB *mysql = pool_.front();
                if (difftime(now, mysql->GetLastTime()) >= MAX_LIVE_TIME) {
                    pool_.pop();
                    delete mysql;
                    --now_conn_count_;
                } else {
                    //未超时,第一个未超时的连接在等待剩余存活时间之后就会超时
                    //所以我们等待这么久加1秒，多加一秒可能因为有过期时间很接近的多个连接
                    sleep_time = difftime(now, mysql->GetLastTime()) + 1;
                    break;
                }
            }
        }
        this_thread::sleep_for(chrono::seconds(sleep_time));
    }
}
