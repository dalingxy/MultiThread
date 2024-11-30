#include "Tasks.h"

bool Tasks::empty() {
    return tasksQueue.empty();
}

function<void()> Tasks::pop() {
    unique_lock<mutex> lock(mtx);
 
    //当任务队列不为空时，可以从中取出一个任务
    cv.wait(lock, [this]{return !tasksQueue.empty();});
    auto task = move(tasksQueue.front()); 
    tasksQueue.pop();
    
    //返回可执行任务【可通过task()调用】
    return task;
}
