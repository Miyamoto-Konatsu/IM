#ifndef TIMER_HEAP_GP
#define TIMER_HEAP_GP
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>
using namespace std;
namespace gp {
const int64_t MAX_NSEC = 1000000000;

using TimerCallback = std::function<void()>;
using EventCallback = std::function<void()>;

using SecondType = long;
using NanoSecondType = long;

#define handle_error(msg)                                                      \
    do {                                                                       \
        perror(msg);                                                           \
        exit(EXIT_FAILURE);                                                    \
    } while (0)

template <typename T, typename Comp> class Heap {
  public:
    Heap() : size_(0), comp_(Comp()) { data_.resize(1); }

    void Push(T value) {
        ++size_;
        if (size_ == data_.size()) {
            data_.push_back(value);
        } else {
            data_[size_] = value;
        }
        PercolateUp(size_);
    }

    T Top() {
        Check();
        return data_[1];
    }

    void Pop() {
        Check();
        swap(data_[1], data_[size_]);
        --size_;
        PercolateDown(1);
    }

    bool Empty() { return size_ == 0; }

  private:
    /*堆里没有元素时进行Top和Pop抛出异常*/
    void Check() {
        if (size_ <= 0) {
            throw logic_error("Heap is empty.");
        }
    }
    /*向上调整*/
    void PercolateUp(int index) {
        T value = data_[index];
        int parent_index = index / 2;
        while (parent_index >= 1) {
            if (comp_(data_[parent_index], value)) {
                data_[index] = data_[parent_index];
                index = parent_index;
                parent_index /= 2;
            } else {
                break;
            }
        }
        data_[index] = value;
    }
    /*向下调整*/
    void PercolateDown(int index) {
        T value = data_[index];
        int child_index = index * 2;
        while (child_index <= size_) {
            if (child_index + 1 <= size_) {
                if (comp_(data_[child_index], data_[child_index + 1])) {
                    ++child_index;
                }
            }
            if (comp_(value, data_[child_index])) {
                data_[index] = data_[child_index];
                index = child_index;
                child_index *= 2;
            } else {
                break;
            }
        }
        data_[index] = value;
    }
    vector<T> data_; // 合法情况下 data_.size() 至少比size_多一。
    Comp comp_;
    int size_; //最后一个元素的下标，下标从一开始。为0时表示堆里没有元素。
};
class TimerObject;

class Timestamp {
  public:
    Timestamp() : ts_(new timespec) {
        ts_->tv_sec = 0;
        ts_->tv_nsec = 0;
    }

    static Timestamp Now() {
        Timestamp timer_stamp;
        clock_gettime(CLOCK_REALTIME, timer_stamp.ts_.get());
        return timer_stamp;
    }

    bool operator<(const Timestamp &rhs) const {
        if (ts_->tv_sec != rhs.GetExpireSecond()) {
            return ts_->tv_sec < rhs.GetExpireSecond();
        }
        return ts_->tv_nsec < rhs.GetExpireNanoSecond();
    }

    Timestamp &AddTime(SecondType second, NanoSecondType nsec = 0) {
        if (second < 0 || nsec < 0) {
            throw invalid_argument("The arguments must >= 0!");
        }
        if (nsec >= MAX_NSEC) {
            throw invalid_argument("The nsec must < 1000000000!");
        }
        ts_->tv_sec += second;
        ts_->tv_nsec += nsec;
        if (ts_->tv_nsec >= MAX_NSEC) {
            ts_->tv_nsec %= MAX_NSEC;
            ts_->tv_sec += 1;
        }
        return *this;
    }

    SecondType GetExpireSecond() const { return ts_->tv_sec; }
    NanoSecondType GetExpireNanoSecond() const { return ts_->tv_nsec; }

  private:
    shared_ptr<timespec> ts_;
};

class TimerObject {
  public:
    template <typename T1, typename T2>
    explicit TimerObject(T1 &&timer_callback, T2 &&expire)
        : timer_callback_(forward<T1>(timer_callback)),
          expire_(forward<T2>(expire)) {}

    void operator()() { timer_callback_(); }

    bool operator<(const TimerObject &rhs) const {
        return expire_ < rhs.expire_;
    }
    const Timestamp &GetTimeStamp() { return expire_; }

  private:
    TimerCallback timer_callback_;
    Timestamp expire_;
};

class Locker {
  public:
    void Lock() { mtx_.lock(); }
    void Unlock() { mtx_.unlock(); }

  private:
    mutex mtx_;
};
/*
 小根堆
*/
struct TimerObjectComp {
    bool operator()(TimerObject *lhs, TimerObject *rhs) {
        return !(*lhs < *rhs);
    }
};

class EventLoop {
  public:
    EventLoop() { epoll_fd_ = epoll_create(1); }
    void Loop() {
        epoll_event ep_event[4];
        while (running) {
            int r = epoll_wait(epoll_fd_, ep_event, 4, -1);
            if (r < 0 && errno != EINTR && errno != EAGAIN) {
                handle_error("epoll wait error");
            }
            for (int i = 0; i < r; ++i) {
                int fd = ep_event[i].data.fd;
                EventCallback ec;
                bool run = false;
                lock.Lock();
                if (fd2ec_.find(fd) != fd2ec_.end()) {
                    run = true;
                    ec = fd2ec_[fd];
                }
                fd2ec_.erase(fd);
                lock.Unlock();
                if (run) {
                    ec();
                }
                Epoll_Del(fd, EPOLLIN);
            }
        }
    }

    /*
     Thread safe
    */
    void Register(int fd, EventCallback ec) {
        lock.Lock();
        fd2ec_[fd] = move(ec);
        lock.Unlock();
        Epoll_Add(fd, EPOLLIN);
    }

  private:
    void Epoll_Add(int fd, uint32_t events, int epoll_fd = -1) {
        if (-1 == epoll_fd)
            epoll_fd = epoll_fd_;
        struct epoll_event ev;
        ev.events = events;
        ev.data.fd = fd;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) == -1) {
            perror("epoll_ctl");
            exit(-1);
        }
    }

    void Epoll_Del(int fd, uint32_t events, int epoll_fd = -1) {
        if (-1 == epoll_fd)
            epoll_fd = epoll_fd_;
        struct epoll_event ev;
        ev.events = events;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &ev) == -1) {
            perror("epoll_ctl");
            exit(-1);
        }
    }
    unordered_map<int, EventCallback> fd2ec_;
    int epoll_fd_;
    bool running = true;
    Locker lock;
};

class TimerHeap {
  public:
    /*
    Thread Safe
    */
    TimerObject *AddTimer(TimerCallback tc, Timestamp ts) {
        int timer_fd = timerfd_create(CLOCK_REALTIME, 0);
        itimerspec its;
        its.it_value.tv_sec = ts.GetExpireSecond();
        its.it_value.tv_nsec = ts.GetExpireNanoSecond();
        its.it_interval.tv_sec = 0;
        its.it_interval.tv_nsec = 0;
        TimerObject *timer_object = new TimerObject(move(tc), move(ts));

        timerfd_settime(timer_fd, TFD_TIMER_ABSTIME, &its, nullptr);

        lock_.Lock();
        timer_object_queue_.Push(timer_object);
        lock_.Unlock();
        loop_->Register(timer_fd, bind(&TimerHeap::Process, this));

        return timer_object;
    }

    TimerHeap(EventLoop *loop) : loop_(loop) {}

  private:
    void Process() {
        Timestamp now = Timestamp::Now();
        while (true) {
            lock_.Lock();
            if (timer_object_queue_.Empty() ||
                now < timer_object_queue_.Top()->GetTimeStamp()) {
                lock_.Unlock();
                break;
            }
            auto *timer_object = timer_object_queue_.Top();
            timer_object_queue_.Pop();
            lock_.Unlock();
            (*timer_object)();
        }
    }

    Locker lock_;
    Heap<TimerObject *, TimerObjectComp> timer_object_queue_;
    EventLoop *loop_;
};
}; // namespace gp

#endif