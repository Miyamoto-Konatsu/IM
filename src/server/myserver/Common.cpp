#include "server/myserver/Common.h"
using std::cout;
using std::endl;

void SetNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    flags |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flags);
}

void debug_message(const string &message) {
#ifdef debug
    cout << (message) << endl;
#endif
}