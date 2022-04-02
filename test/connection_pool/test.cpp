#include "server/db/ConnectionPool.h"
#include <atomic>
#include <chrono>
#include <random>
#include <thread>
#include <vector>

using namespace std;
atomic<int> count{0};
int target = 500;

void concurrent_test() {
    ConnectionPool *pool = ConnectionPool::GetInstance();
    char sql[100] = {0};
    // sprintf(sql, "insert into test values (null, '123456')");
    while (count++ < target) {
        auto mysql = pool->GetConnction();
        this_thread::sleep_for(chrono::milliseconds(100));
        cout << "get connection" << endl;
        // mysql->ExecSql(sql);
    }
}

int main() {
    vector<thread> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(thread(&concurrent_test));
    }
    for (int i = 0; i < 100; ++i) {
        v[i].join();
    }
    cout << "end" << endl;
    return 0;
}