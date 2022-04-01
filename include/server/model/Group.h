#ifndef GROUP_H
#define GROUP_H
#include "server/model/User.h"
#include <string>
#include <vector>
using namespace std;

class Group {
  public:
    Group() = default;

    Group(int id, const string &group_name, const string &group_desc)
        : id_(id), group_name_(group_name), group_desc_(group_desc) {}

    Group(const string &group_name, const string &group_desc)
        : id_(-1), group_name_(group_name), group_desc_(group_desc) {}

    void SetGroupName(const string &group_name) {
        this->group_name_ = group_name;
    }
    void SetGroupDesc(const string &group_desc) {
        this->group_desc_ = group_desc;
    }
    void SetGroupId(int id) { this->id_ = id; }
    void SetGroupUser(const vector<GroupUser> &users) { this->users_ = users; }

    const string &GetGroupName() const { return this->group_name_; }
    const string &GetGroupDesc() const { return this->group_desc_; }
    int GetGroupId() const { return this->id_; }
    vector<GroupUser> &GetGroupUser() { return this->users_; }

  private:
    int id_;
    string group_name_;
    string group_desc_;
    vector<GroupUser> users_;
};
#endif