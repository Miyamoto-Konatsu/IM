#ifndef MY_MYSQL_H
#define MY_MYSQL_H
#include <iostream>
#include <mysql/mysql.h>
#include <string>
#include <time.h>
using namespace std;

class MySQLDB {
  public:
    MySQLDB();
    ~MySQLDB();
    bool InitDB(const string &host = "127.0.0.1", const string &user = "root",
                const string &passwd = "root",
                const string &db_name = "Chat"); //连接mysql
    bool ExecSql(char *sql);                     //执行sql语句
    MYSQL *GetMysqlPtr() { return this->mysql_ptr; }
    time_t GetLastTime() { return last_time_; }
    void ResetLastTime() { last_time_ = time(nullptr); }

  private:
    MYSQL *mysql_ptr; //连接mysql句柄指针
    time_t last_time_;
};

#endif