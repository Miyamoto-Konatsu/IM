#include "server/db/MySQL.h"

MySQLDB::MySQLDB() : last_time_(time(nullptr)) {
    mysql_ptr = mysql_init(nullptr);
    if (mysql_ptr == nullptr) {
        cout << "Error: " << mysql_error(mysql_ptr);
        cout << "初始化数据库失败" << endl;
        exit(-1);
    }
    InitDB();
}

MySQLDB::~MySQLDB() {
    if (mysql_ptr != nullptr) {
        mysql_close(mysql_ptr);
    }
}

bool MySQLDB::InitDB(const string &host, const string &user,
                     const string &passwd, const string &db_name) {
    mysql_ptr =
        mysql_real_connect(mysql_ptr, host.c_str(), user.c_str(),
                           passwd.c_str(), db_name.c_str(), 3306, nullptr, 0);
    if (mysql_ptr == nullptr) {
        cout << "连接数据库失败:" << mysql_errno(mysql_ptr);
        cout << "连接数据库失败";
        exit(-1);
    }
    return true;
}

bool MySQLDB::ExecSql(char *sql) {
    if (mysql_query(mysql_ptr, sql)) { //执行成功返回0，失败返回非0值。
        cout << "Error:" << sql << " failed" << endl;
        return false;
    }
    return true;
}