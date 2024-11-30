#include <type_traits>

#include "ThreadPool.h"

using namespace std;

ThreadPool::ThreadPool(size_t num) 
    : initWorkerNum(num) 
    , isRunning(true)
{
    //创建工作线程
    for(int i=0; i<initWorkerNum; ++i)        
        workThreads.push_back( thread(&ThreadPool::worker, this) ); 
}

ThreadPool::~ThreadPool() {
    isRunning = false;

    //释放线程池之前，确保正在进行的线程能够执行完任务
    for(auto& thd : workThreads)
        if(thd.joinable())
            thd.join();
}

void ThreadPool::worker() {
    while(true) {   //各线程始终监听任务队列，等待从中取出任务
        if(!isRunning && tasks.empty())
            return;

        auto task = tasks.pop();
        cout << "Thread_" << this_thread::get_id() << " is executing..." << endl;
        task();
        this_thread::sleep_for(2s);
    }
}

