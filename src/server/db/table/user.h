#ifndef USER_TABLE_H
#define USER_TABLE_H

#include "odb/core.hxx"
#include <string>

using namespace odb::core;

#pragma db object table("User")
class User {
public:
    User() {
    }

    User(const std::string &userId, const std::string &password,
         const std::string &nickname) :
        userId_(userId),
        password_(password), nickname_(nickname) {
    }

    User(const User &user) = default;
    User(User &&user) = default;
    
    const unsigned long &id() const {
        return id_;
    }

    const std::string &userId() const {
        return userId_;
    }

    void userId(const std::string &userId) {
        userId_ = userId;
    }

    const std::string &password() const {
        return password_;
    }

    void password(const std::string &password) {
        password_ = password;
    }

    const std::string &nickname() const {
        return nickname_;
    }

    void nickname(const std::string &nickname) {
        nickname_ = nickname;
    }

public:
    friend class odb::access;

#pragma db id auto
    unsigned long id_;
#pragma db index unique member(userId_, "(32)")
    std::string userId_;
#pragma db not_null
    std::string password_;
#pragma db not_null
    std::string nickname_;
};
#endif