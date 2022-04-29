#pragma once
#include "server/myserver/Common.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

class TcpError : public exception {
  public:
    TcpError() : exception() {}
    ~TcpError() {}
    const char *what() { return "Tcp connection meets an error\n"; }
};

class TcpDisc : public exception {
  public:
    TcpDisc() : exception() {}
    ~TcpDisc() {}
    const char *what() { return "Tcp connection disconnects\n"; }
};

class Buffer {
  public:
    Buffer() = default;
    /*
    ----------------------------------
        tailer|     data       |header
    ----------------------------------
    */
    int Read(int fd) {
        if (full_)
            return BUFFER_SIZE;
        char buf_temp[BUFFER_SIZE];
        int count = read(fd, buf_temp, SpaceRest());
        if (0 == count) {
            //断开连接
            TcpDisc tcp_disc;
            throw tcp_disc;
        } else if (-1 == count) {
            //不是重试
            if (EAGAIN != errno) {
                TcpError tcp_error;
                throw tcp_error;
            }
        } else {
            for (int i = 0; i < count; ++i) {
                buffer_[(header_ + i) % BUFFER_SIZE] = buf_temp[i];
            }
            HeaderMove(count);
            if (tailer_ == header_) {
                full_ = true;
            }
        }
        return SpaceUsed();
    }
    int Readable_Size() { return SpaceUsed(); } //可读字节数

    void Retrieve(int size) { //释放size字节的缓冲区空间
        if (0 >= size)
            return;
        size = SuitableSize(size);
        TailerMove(size);
        full_ = false;
    }

    string Peek(int size = 4096) { // 返回buf的前size字节，但不释放size字节的空间
        if (0 >= size)
            return string();
        size = SuitableSize(size);
        string res(size, ' ');
        for (int i = 0; i < size; ++i) {
            res[i] = buffer_[(tailer_ + i) % BUFFER_SIZE];
        }
        return res;
    }

    ~Buffer() { debug_message("release buffer"); }

  private:
    int SuitableSize(int size) {
        if (full_) {
            size = min(size, BUFFER_SIZE);
        } else {
            size = min(size, SpaceUsed());
        }
        return size;
    }

    int SpaceRest() {
        return BUFFER_SIZE - SpaceUsed();
    }

    int SpaceUsed() {
        int size = (header_ + BUFFER_SIZE - tailer_) % BUFFER_SIZE;
        if (0 == size) {
            return full_ ? BUFFER_SIZE : 0;
        }
        return size;
    }

    void HeaderMove(int size) { header_ = (header_ + size) % BUFFER_SIZE; }
    void TailerMove(int size) { tailer_ = (tailer_ + size) % BUFFER_SIZE; }

    char buffer_[BUFFER_SIZE];
    int header_ = 0;
    int tailer_ = 0;
    bool full_ = false;
};
class Connection;
typedef std::function<void(Connection *, Buffer *)> MessageCallback;
typedef std::function<void(Connection *)> ConnectionCallback;

class MyServer;

class Connection {
  public:
    Connection(MyServer *server, int fd) : server_(server), fd_(fd) {}
    void Read();

    void Send(const void *message, int len);

    bool Disconnected() { return disconnected; }

  private:
    
    Buffer buffer_;
    int fd_;
    bool disconnected = false;
    MyServer *server_;
};