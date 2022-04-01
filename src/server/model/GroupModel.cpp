#include "server/model/GroupModel.h"
#include "server/db/ConnectionPool.h"
#include "server/model/UserModel.h"
bool GroupModel::InsertGroup(Group &group) {
    char sql[1024] = {0};
    char format[] = "insert into allgroup values (null, '%s' , '%s')";
    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    sprintf(sql, format, group.GetGroupName().c_str(),
            group.GetGroupDesc().c_str());
    if (!(mysql->ExecSql(sql))) {
        return false;
    }

    //获取插入后的id
    int id = mysql_insert_id(mysql->GetMysqlPtr());
    group.SetGroupId(id);
    return true;
}

bool GroupModel::InsertGroupUser(int group_id, int user_id, string role) {
    char sql[1024] = {0};
    char format[] = "insert into groupuser values ('%d' , '%d', '%s')";
    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    sprintf(sql, format, group_id, user_id, role.c_str());
    if (!(mysql->ExecSql(sql))) {
        return false;
    }
    return true;
}

unique_ptr<vector<Group>> GroupModel::QueryGroup(int user_id) {
    char sql[100] = {0};
    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    //查询groupuser表获得该用户所在的群
    sprintf(sql,
            "select groupid from "
            "groupuser "
            "where userid = '%d'",
            user_id);
    if (!mysql->ExecSql(sql)) {
        return nullptr;
    }

    auto res = new vector<Group>{};
    vector<int> group_ids;
    MYSQL *mysql_ptr = mysql->GetMysqlPtr();
    MYSQL_RES *result = mysql_use_result(mysql_ptr);
    MYSQL_ROW row = mysql_fetch_row(result);
    while (row != nullptr) {
        // row[0]是group_id
        group_ids.push_back(atoi(row[0]));
        row = mysql_fetch_row(result);
    }
    mysql_free_result(result);

    UserModel user_model;
    //查询每个群和它的组员
    char sql_format[] = "select * from allgroup where id = %d";
    for (auto group_id : group_ids) {
        sprintf(sql, sql_format, group_id);
        if (!mysql->ExecSql(sql)) {
            return nullptr;
        }
        mysql_ptr = mysql->GetMysqlPtr();
        result = mysql_use_result(mysql_ptr);
        row = mysql_fetch_row(result);
        while (row != nullptr) {
            // row[0]是group_id,row存的是群的信息
            res->emplace_back(atoi(row[0]), row[1], row[2]);
            auto group_users = QueryGroupUser(atoi(row[0]));
            GroupUser group_user;
            for (auto &id_role : *group_users) {
                user_model.QueryUser(id_role.first, group_user);
                group_user.SetRole(id_role.second);
                res->back().GetGroupUser().push_back(group_user);
            }
            row = mysql_fetch_row(result);
        }
        mysql_free_result(result);
    }

    return unique_ptr<vector<Group>>{res};
}

unique_ptr<vector<pair<int, string>>> GroupModel::QueryGroupUser(int group_id) {
    char sql[1024] = {0};
    char format[] =
        "select userid, grouprole from groupuser where groupid = %d";

    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    sprintf(sql, format, group_id);
    if (!(mysql->ExecSql(sql))) {
        return nullptr;
    }

    auto res = new vector<pair<int, string>>{};

    MYSQL *mysql_ptr = mysql->GetMysqlPtr();
    MYSQL_RES *result = mysql_use_result(mysql_ptr);
    MYSQL_ROW row = mysql_fetch_row(result);

    while (row != nullptr) {
        res->push_back({atoi(row[0]), row[1]});
        row = mysql_fetch_row(result);
    }
    mysql_free_result(result);

    return unique_ptr<vector<pair<int, string>>>{res};
}