#include "Log.h"
#include <thread>
#include <mutex>
#include <iostream>
using namespace std;

mutex log_mtx;

void log(const std::string& str){
    unique_lock<mutex> lk(log_mtx);
    cout << str << endl;
}

void logerr(const std::string& str){
    unique_lock<mutex> lk(log_mtx);
    cerr << str << endl;
}
