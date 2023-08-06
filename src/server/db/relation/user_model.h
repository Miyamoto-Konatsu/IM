#ifndef USER_RELATION_H
#define USER_RELATION_H

#include "table/user.h"
#include <memory>
#include <odb/database.hxx>
#include <odb/transaction.hxx>
#include <odb/session.hxx>
#include <odb/mysql/database.hxx>
#include <vector>
#include "table/user-odb.hxx"
#include "utils.h"
#include "common.h"

class UserModel {
public:
    UserModel() : db(getDB()) {
    }

    // 创建 User 对象
    void createUser(User &user) {
        odb::transaction t(db->begin());
        auto query =
            db->query_one<User>(odb::query<User>::userId == user.userId());
        if (query) { throw DatabaseLookupError("User already exists"); }
        db->persist(user); // 将对象插入数据库
        t.commit();        // 提交事务
    }

    // 查询 User 对象
    User findUser(const std::string &userId) {
        odb::transaction t(db->begin());
        odb::query<User> query(odb::query<User>::userId == userId);
        User result;

        auto isFound = db->query_one(query, result);
        t.commit(); // 提交事务
        if (isFound) {
            return result;
        } else {
            throw DatabaseLookupError("User not found");
        }
    }

    // 查询 User 对象
    User findUser(const unsigned long &id) {
        odb::transaction t(db->begin());
        odb::query<User> query(odb::query<User>::id == id);
        User result;

        auto isFound = db->query_one(query, result);
        t.commit(); // 提交事务
        if (isFound) {
            return result;
        } else {
            throw DatabaseLookupError("User not found");
        }
    }

private:
    std::shared_ptr<odb::database> db;
};
#endif