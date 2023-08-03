#ifndef MSGHANDLER_COMMON_H
#define MSGHANDLER_COMMON_H
#include <memory>
#include <queue>
#include <condition_variable>
#include "consumer.h"
#include "producer.h"

class MsgHandler {
public:
    MsgHandler() = default;
    virtual ~MsgHandler() = default;
    MsgHandler(const MsgHandler &) = delete;
    MsgHandler &operator=(const MsgHandler &) = delete;

    virtual void run() = 0;

protected:
    virtual void stop() = 0;
};

template <typename T>
class BlockChannel {
private:
    std::queue<T> queue_;               // 存储管道中的元素的队列
    std::unique_ptr<std::mutex> mutex_; // 用于保护队列的互斥锁
    std::unique_ptr<std::condition_variable> cv_; // 用于线程同步的条件变量
    volatile bool closed_ = false;                // 标记管道是否关闭
public:
    BlockChannel() : mutex_(new std::mutex), cv_(new std::condition_variable) {
        std::cerr << "BlockChannel()" << std::endl;
    };
    ~BlockChannel() = default;
    BlockChannel(const BlockChannel &) = delete;
    BlockChannel &operator=(const BlockChannel &) = delete;
    BlockChannel(BlockChannel &&) = default;
    BlockChannel &operator=(BlockChannel &&) = default;

    // 发送数据到管道（支持右值引用）
    void send(T &&value) {
        {
            std::lock_guard<std::mutex> lock(*mutex_);
            if (closed_) { return; }
            queue_.push(std::move(value));
        }
        cv_->notify_one();
    }

    // 从管道接收数据（支持右值引用）
    T receive() {
        std::unique_lock<std::mutex> lock(*mutex_);
        while (queue_.empty() && !closed_) { cv_->wait(lock); }
        if (closed_ && queue_.empty()) {
            throw std::runtime_error("receive from closed empty BlockChannel");
        }
        T value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    void close() {
        std::lock_guard<std::mutex> lock(*mutex_);
        closed_ = true;
        cv_->notify_all();
    }
};
#endif