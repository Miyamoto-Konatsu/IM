#include "server/model/FriendModel.h"

bool FriendModel::Insert(int user_id1, int user_id2) {
    char sql[50] = {0};
    char format[] = "insert into friend values ('%d' , '%d')";
    MySQLDB mysql;
    sprintf(sql, format, user_id1, user_id2);
    if (!(mysql.ExecSql(sql))) {
        return false;
    }
    sprintf(sql, format, user_id2, user_id1);
    if (!(mysql.ExecSql(sql))) {
        return false;
    }
    return true;
}

unique_ptr<vector<User>> FriendModel::GetFriend(int user_id) {
    vector<User> friends;
    MySQLDB mysql;
    char sql[150] = {0};
    vector<User> *vec_ptr = new vector<User>();

    sprintf(sql,
            "select user.id, user.nickname, user.password, user.state from "
            "user , friend "
            "where friend.id = '%d' and user.id = friend.friendid",
            user_id);
    if (!mysql.ExecSql(sql)) {
        LOG_DEBUG << user_id << " retrieve friends failed";
        return unique_ptr<vector<User>>(vec_ptr);
    }
    MYSQL *mysql_ptr = mysql.GetMysqlPtr();
    MYSQL_RES *result = mysql_use_result(mysql_ptr);
    MYSQL_ROW row = mysql_fetch_row(result);
    while (row != nullptr) {
        vec_ptr->emplace_back(atoi(row[0]), row[1], row[2], row[3]);
        row = mysql_fetch_row(result);
    }
    mysql_free_result(result);
    return unique_ptr<vector<User>>(vec_ptr);
}