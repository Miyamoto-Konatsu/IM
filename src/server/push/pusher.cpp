#include "pusher.h"

Pusher::Pusher() {
}

Pusher::~Pusher() {
}

bool Pusher::PushMsg2User(const msg &msg) {
    std::cout << msg.fromuserid() << ' ' << msg.touserid() << ' '
              << msg.content() << std::endl;
    return true;
}
