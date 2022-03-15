#ifndef MY_MYSQL_H
#define MY_MYSQL_H
#include <iostream>
#include <mysql/mysql.h>
#include <string>

using namespace std;

class MySQLDB {
  public:
    MySQLDB();
    ~MySQLDB();
    bool InitDB(const string &host = "127.0.0.1", const string &user = "root", const string &passwd = "root",
                const string &db_name = "Chat"); //连接mysql
    bool ExecSql(char *sql);            //执行sql语句
    MYSQL *GetMysqlPtr() { return this->mysql_ptr; }
  private:
    MYSQL *mysql_ptr;  //连接mysql句柄指针
    MYSQL_RES *result; //指向查询结果的指针
    MYSQL_ROW row;     //按行返回的查询信息
};

#endif