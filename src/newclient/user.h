#ifndef USER_NEWCLIENT_H
#define USER_NEWCLIENT_H
#include <string>
class User {
public:
    User() {
    }
    User(const std::string &userID, const std::string &password,
         const std::string &secret) :
        userID_(userID),
        password_(password), secret_(secret) {
    }

    // setter
    void setUserID(const std::string &userID) {
        userID_ = userID;
    }
    void setPassword(const std::string &password) {
        password_ = password;
    }
    void setSecret(const std::string &secret) {
        secret_ = secret;
    }
    void setToken(const std::string &token) {
        token_ = token;
    }
    // getter
    std::string getUserID() const {
        return userID_;
    }
    std::string getPassword() const {
        return password_;
    }
    std::string getSecret() const {
        return secret_;
    }
    std::string getToken() const {
        return token_;
    }

private:
    std::string userID_;
    std::string password_;
    std::string secret_;
    std::string token_;
};
#endif