#ifndef USER_H
#define USER_H
#include <string>
using namespace std;
class User {
  public:
    enum class STATE { online = 0, offline };
    
    User( std::string nickname, std::string password)
        : nickname_(nickname), password_(password) {}
        
    void SetUserId(int user_id){this->user_id_ = user_id;}
    void SetNickname(std::string nickname) { this->nickname_ = nickname; }
    void SetPassword(std::string password) { this->password_ = password; }
    void SetState(STATE state) { this->state_ = state; }


    std::string GetNickname() { return this->nickname_; }
    std::string GetPassword() { return this->password_; }
    std::string GetNickname() { return this->nickname_; }
    STATE GetState() { return this->state_; }

  private:
    std::string nickname_;
    int user_id_;
    std::string password_;
    STATE state_;
};
#endif