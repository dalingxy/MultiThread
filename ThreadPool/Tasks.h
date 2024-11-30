#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>
#include <future>

using namespace std;

class Tasks
{
public:
    Tasks() = default;
    ~Tasks() = default;
   bool empty();

    //“添加任务”
    //模板函数需要在头文件中进行定义，而不仅仅是声明。
    //否则，在链接阶段编译器将找不到其实现，导致undefined reference
    template<class Func, class... Args>
    auto push(Func&& f, Args&& ...args)->future<decltype(f(args...))>;
    
    //"取出任务"
    function<void()> pop();
    
private:
    queue<function<void()>> tasksQueue; //任务队列
    mutex mtx;              //互斥锁
    condition_variable cv;  //条件变量
};

template<class Func, class ...Args>
auto Tasks::push(Func&& f, Args&&... args)->future<decltype(f(args...))>{
    //获取函数的返回类型
    using returnType = decltype(f(args...));

    //包装任务
    //1.通过bind()，将原任务及其传入的参数相绑定
    //2.通过packaged_task<>包装，以便异步获取执行结果(future)
    auto task = make_shared< packaged_task<returnType()> >(
        bind(forward<Func>(f), forward<Args>(args)...)
    );
    
    //绑定future对象，以便返回结果
    future<returnType> taskFuture = task->get_future();
    
    //将task添加到任务队列
    {
        lock_guard<mutex> lock(mtx);
        tasksQueue.push([task](){ (*task)(); });
    }

    //唤醒阻塞进程
    cv.notify_one();
 
    return taskFuture;
 }
