#include "server/db/ConnectionPool.h"
#include <atomic>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

using namespace std;
atomic<int> count{0};
int target = 50000;

void concurrent_test() {
    ConnectionPool *pool = ConnectionPool::GetInstance();
    char sql[100] = {0};
    sprintf(sql, "insert into test values (null, '123456')");
    while (count++ < target) {
        auto mysql = pool->GetConnction();
        mysql->ExecSql(sql);
    }
}

void test(int nums) {
    char sql[100] = {0};
    sprintf(sql, "insert into test values (null, '123456')");
    for (int i = 0; i < nums; ++i) {
        MySQLDB mysql;
        mysql.ExecSql(sql);
    }
}

int main() {
    thread t1(&concurrent_test);
    thread t2(&concurrent_test);
    thread t3(&concurrent_test);
    t2.join();
    t1.join();
    t3.join();
    return 0;
}