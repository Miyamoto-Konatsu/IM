#ifndef CONNECTION_POOL_H
#define CONNECTION_POOL_H
#include "server/db/MySQL.h"
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <queue>
#include <mutex>
#include <mysql/mysql.h>
#include <string>
#include <thread>
using namespace std;

const int MAX_CONNECTION = 128;
const int MIN_CONNECTION = 8;
const int MAX_LIVE_TIME = 60; //一个连接在60s内未使用则释放

using retconnfunc = function<void(MySQLDB *)>;

class ConnectionPool {
  public:
    static ConnectionPool *GetInstance() {
        static ConnectionPool pool;
        return &pool;
    }

    unique_ptr<MySQLDB, retconnfunc> GetConnction();

  private:
    ~ConnectionPool();
    void ReturnConnection(MySQLDB *);
    void ReleaseConnection();
    ConnectionPool();

    mutex mtx_;
    condition_variable cv_;
    int now_conn_count_;

    atomic<bool> pool_alive_;
    thread release_thread_;
    queue<MySQLDB *> pool_;

    const int min_connection_;
    const int max_connection_;
};

#endif