#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;

//全局互斥量
mutex mtx;
condition_variable cv;
bool sharedValue = false;

void WorkerThread(int Tid) {
    unique_lock<mutex> lock(mtx);
    cv.wait(lock, []{return sharedValue;});
    cout << "WorkerThread_" << Tid << " is running." << endl;
}
void MainThread(){
    {
        lock_guard<mutex> lock(mtx);
        sharedValue = true;
    }
    cout << "MainThread is running." << endl;
    cout << "notify WorkerThreads." << endl;
    
    cv.notify_all();
}

void test(int n) {
    thread mainT(MainThread);
    vector<thread> workerT(n);
    for(int i=1; i<=n; ++i)
        workerT[i-1] = thread(WorkerThread, i);
    
    for(auto& t : workerT) 
        t.join();
    mainT.join();
}

int main()
{
    test(5);
    return 0;
}

