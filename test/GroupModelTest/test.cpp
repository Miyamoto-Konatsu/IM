#include "server/model/Group.h"
#include "server/model/GroupModel.h"
#include "server/model/User.h"
#include "server/model/UserModel.h"
int main() {
    GroupModel group_model;
    UserModel user_model;

    Group group;
    User user;

    user_model.QueryUser(18, user);
    group.SetGroupName("chat");
    group.SetGroupDesc("chat together");
    group_model.InsertGroup(group);
    group_model.InsertGroupUser(group.GetGroupId(), user.GetUserId(),
                                "creator");
    auto group_vec = group_model.QueryGroup(user.GetUserId());
    return 0;
}