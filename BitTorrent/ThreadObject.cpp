#include "ThreadObject.h"
#include <iostream>
#include "Log.h"
using namespace std;

ThreadObject::ThreadObject():my_thread{bind(&ThreadObject::handle_task, this)}, state{ThreadState::RUNNING}{}

ThreadObject::~ThreadObject() {
    stop();
    if (my_thread.joinable()) {
        my_thread.join();
    }
   // log("thread done");
}

bool ThreadObject::add_task(std::function<void(void)> task){
    unique_lock<mutex> lkg(mtx);
    if (state == ThreadState::DONE) {
        return false;
    }
    tasks.push(task);
    cv.notify_all();
    return true;
}

void ThreadObject::stop(){
    unique_lock<mutex> lkg(mtx);
    state = ThreadState::DONE;
    cv.notify_all();
}

void ThreadObject::stop_when_done(){
    unique_lock<mutex> lkg(mtx);
    state = ThreadState::FINISH_TASK_AND_DONE;
    cv.notify_all();
}

void ThreadObject::join(){
    return my_thread.join();
}

void ThreadObject::handle_task(){
    while (get_task()) task();
}

bool ThreadObject::get_task(){
    unique_lock<mutex> lkg(mtx);
    while (tasks.empty() && state == ThreadState::RUNNING) {
        cv.wait(lkg);
    }
    if (!tasks.empty() && state != ThreadState::DONE) {
        task = tasks.front();
        tasks.pop();
        return true;
    } else {
        state = ThreadState::DONE;
        return false;
    }
}