#include "server/model/OfflineMessageModel.h"
#include "server/db/ConnectionPool.h"

bool OfflineMessageModel::Insert(int user_id, const string &message) {
    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    char sql[600] = {0};
    sprintf(sql, "insert into offlinemessage values ('%d', '%s')", user_id,
            message.c_str());
    if (!mysql->ExecSql(sql)) {
        return false;
    }
    return true;
}

void OfflineMessageModel::Delete(int user_id) {
    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    char sql[100] = {0};
    sprintf(sql, "delete from offlinemessage where id = '%d'", user_id);
    mysql->ExecSql(sql);
}

unique_ptr<vector<string>> OfflineMessageModel::Query(int user_id) {
    auto mysql = ConnectionPool::GetInstance()->GetConnction();
    char sql[100] = {0};
    sprintf(sql, "select message from offlinemessage where id = '%d'", user_id);
    vector<string> *vec = new vector<string>();
    if (!mysql->ExecSql(sql)) {
        return unique_ptr<vector<string>>(vec);
    }
    MYSQL *mysql_ptr = mysql->GetMysqlPtr();
    MYSQL_RES *res = mysql_use_result(mysql_ptr);
    MYSQL_ROW row = mysql_fetch_row(res);
    while (row) {
        vec->push_back(row[0]);
        row = mysql_fetch_row(res);
    }
    mysql_free_result(res);
    return unique_ptr<vector<string>>(vec);
}