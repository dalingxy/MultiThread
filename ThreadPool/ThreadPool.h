#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <thread>
#include <atomic>

#include "Tasks.h"

using namespace std;

#define maxWorkerNum 8; //线程池允许的最大线程数量

class ThreadPool {
public:
    ThreadPool(size_t num = 4);
    ~ThreadPool();

    //提交一个任务到任务队列
    template<class F, class... Args>
    auto submit(F&& f, Args&&... args)->future<decltype(f(args...))>;

private:
    //void addThread(unsigned int num);  //动态增加线程数量
    
    void worker();                     //工作线程的入口函数

private:
    //ThreadPool分别维护一堆工作线程和一个任务队列
    //使用者可以向任务队列中添加任务；
    //工作线程始终监听任务队列，负责从中取出任务并执行
    vector<thread> workThreads;    //工作线程
    Tasks tasks;                   //任务队列
    
    size_t initWorkerNum;   //线程池启动时，初始化的线程数量  
    bool isRunning;         //线程池是否仍在运行
};


template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args)->future<decltype(f(args...))> {
    return tasks.push(f, args...);
}
