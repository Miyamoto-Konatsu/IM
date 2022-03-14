#ifndef MY_MYSQL_H
#define MY_MYSQL_H
#include<iostream>
#include<string>
#include<mysql/mysql.h>
using namespace std;

class MySQLDB
{
    public:
    MySQLDB();
    ~MySQLDB();
    bool initDB(string host,string user,string pwd,string db_name); //连接mysql
    bool exeSQL(string sql);   //执行sql语句
    private:
    MYSQL *mysql;          //连接mysql句柄指针
    MYSQL_RES *result;    //指向查询结果的指针
    MYSQL_ROW row;       //按行返回的查询信息
};

#endif