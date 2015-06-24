#ifndef THREAD_OBJECT_H
#define THREAD_OBJECT_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <queue>
#include <atomic>

class ThreadObject{
public:
    ThreadObject();
    virtual ~ThreadObject();
    bool add_task(std::function<void(void)> task);
    void stop();
    void stop_when_done();
    void join();
private:
    void handle_task();
    bool get_task();
    std::queue<std::function<void(void)>> tasks;
    std::function<void(void)> task;
    std::thread my_thread;
    
    std::mutex mtx;
    std::condition_variable cv;
    enum class ThreadState{
        RUNNING,
        FINISH_TASK_AND_DONE,
        DONE
    };
    std::atomic<ThreadState>  state;
    
};

#endif
