#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User {
  public:
    User() {}
    User(const std::string &nickname, const std::string &password,
         const std::string &state = "offline")
        : nickname_(nickname), password_(password), state_(state),
          user_id_(-1) {}

    User(int user_id, const std::string &nickname,
         const std::string &password = "", const std::string &state = "offline")
        : user_id_(user_id), nickname_(nickname), password_(password),
          state_(state) {}

    void SetUserId(int user_id) { this->user_id_ = user_id; }
    void SetNickname(std::string nickname) { this->nickname_ = nickname; }
    void SetPassword(std::string password) { this->password_ = password; }
    void SetState(string state) { this->state_ = state; }

    std::string GetNickname() const { return this->nickname_; }
    std::string GetPassword() const { return this->password_; }
    int GetUserId() const { return this->user_id_; }
    string GetState() const { return this->state_; }

  private:
    std::string nickname_;
    int user_id_;
    std::string password_;
    string state_;
};

class GroupUser : public User {
  public:
    GroupUser() = default;
    void SetRole(const string &role) {
        if (role != "creator" && role != "normal")
            throw "role error";
        this->role_ = role;
    }
    const string &GetRole() const { return this->role_; }

  private:
    string role_;
};
#endif