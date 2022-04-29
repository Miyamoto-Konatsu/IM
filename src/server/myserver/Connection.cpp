#include "server/myserver/Connection.h"
#include "server/myserver/MyServer.h"
void Connection::Read() {
    try {
        int size = buffer_.Read(fd_);
        if (size > 0) {
            this->server_->message_callback(this, &this->buffer_);
        }
    } catch (const exception &e) {
        disconnected = true;
        this->server_->connection_callback(this);
        throw;
    }
}

void Connection::Send(const void *message, int len) {
    int size_sent = 0;
    while (size_sent < len) {
        int size = write(fd_, message + size_sent, len - size_sent);
        if (size < 0) {
            if (errno != EAGAIN) {
                disconnected = true;
                this->server_->connection_callback(this);
                TcpError tcp_error;
                throw tcp_error;
            } else {
                continue;
            }
        }
        size_sent += size;
    }
}
