#include "server/myserver/Connection.h"
#include "server/myserver/MyServer.h"
namespace gp {
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
void Connection::Send(shared_ptr<char> message, int len) {
    buffer_.PushSendQueue(message, len);
    DoSend();
}
void Connection::DoSend() {
    while (true) {
        if (buffer_.SendQueueEmpty()) {
            //没数据要发送时，取消监听写事件
            if (sending) {
                server_->Epoll_Ctl(fd_, EPOLLIN | EPOLLERR, epoll_fd_);
            }
            sending = false;
            break;
        }
        auto node = buffer_.SendQueueFront();
        const void *message = node.first;
        int len = node.second;
        ssize_t size = send(fd_, message, len, 0);
        if (size > 0) {
            buffer_.AddSizeSent(size);
            //一次没有全部发送完
            if (size < len) {
                //注册写事件
                if (false == sending) {
                    sending = true;
                    server_->Epoll_Ctl(fd_, EPOLLIN | EPOLLERR | EPOLLOUT,
                                       epoll_fd_);
                }
                break;
            }

        } else if (size == -1) {
            //一个字节都发送不了，缓冲区满了
            if (errno == EAGAIN) {
                if (false == sending) {
                    sending = true;
                    server_->Epoll_Ctl(fd_, EPOLLIN | EPOLLERR | EPOLLOUT,
                                       epoll_fd_);
                }
                break;
            } else {
                TcpError tcp_error;
                throw tcp_error;
            }
        } else {
            TcpDisc tcp_disc;
            throw tcp_disc;
        }
    }
}
} // namespace gp