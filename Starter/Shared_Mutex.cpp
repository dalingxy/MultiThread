// shared_mutex requires C++17

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

shared_mutex sharedMtx;

void Writer(const string& str){
    //写者占用控制台资源，必须独占锁（unique_lock）
    unique_lock<shared_mutex> uniqueLock(sharedMtx);
    
    this_thread::sleep_for(chrono::seconds(3)); //间隔三秒
    cout << "Write: " << str << endl;
}
void Reader(){
    //多个读者进程可以同时进行（shared_lock）
    shared_lock<shared_mutex> sharedLock(sharedMtx);

    this_thread::sleep_for(chrono::seconds(1));
}

void test(){
    vector<thread> threads;
    for(int i=0; i<10; ++i)
        threads.push_back(thread(Reader));
    threads.push_back(thread(Writer, "I own the lock !"));
    threads.push_back(thread(Writer, "The lock is mine."));

    for(auto& td : threads)
        td.join();
}

int main()
{
    test();
    return 0;
}

