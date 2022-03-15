#include "server/model/UserModel.h"
#include <muduo/base/Logging.h>
using namespace muduo;

bool UserModel::Insert(User &user) {

    char sql[200] = {0};
    sprintf(sql,
            "insert into user(nickname, password, state) values ( "
            "'%s','%s','offline')",
            user.GetNickname().c_str(), user.GetPassword().c_str());
    MySQLDB mysql;
    if (!mysql.ExecSql(sql)) {
        LOG_DEBUG << "Insertion failed";
        return false;
    }
    char search[200] = {0};
    sprintf(search,
            "select id, nickname, state from user where nickname = '%s'",
            user.GetNickname().c_str());
    if (!mysql.ExecSql(search)) {
        LOG_DEBUG << "Query failed\n";
        return false;
    }
    MYSQL *mysql_ptr = mysql.GetMysqlPtr();
    MYSQL_RES *result = mysql_use_result(mysql_ptr);
    MYSQL_ROW row = mysql_fetch_row(result);
    user.SetUserId(atoi(row[0]));
    LOG_INFO << "New user:" << user.GetNickname() << " sign up";
    return true;
}

bool UserModel::QueryUser(int user_id, User &user) {
    char sql[100] = {0};
    sprintf(sql, "select * from user where id = '%d'",
            user_id);
    MySQLDB mysql;
    if (!mysql.ExecSql(sql)) {
        LOG_DEBUG << "Query failed";
        return false;
    }
    MYSQL *mysql_ptr = mysql.GetMysqlPtr();
    MYSQL_RES *result = mysql_store_result(mysql_ptr);

    if (result != nullptr) {
        MYSQL_ROW row = mysql_fetch_row(result);
        if (row != nullptr) {
            user.SetUserId(atoi(row[0]));
            user.SetNickname(row[1]);
            user.SetPassword(row[2]);
            user.SetState(row[3]);
            mysql_free_result(result);
            return true;
        }
    }
    return false;
}

bool UserModel::UpdateState(const User &user) {
    char sql[100] = {0};
    sprintf(sql, "update user set state = '%s' where id = '%d'",
            user.GetState().c_str(), user.GetUserId());
    MySQLDB mysql;
    if (!mysql.ExecSql(sql)) {
        LOG_DEBUG << "Update failed";
        return false;
    }
    return true;
}