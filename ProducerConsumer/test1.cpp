#include <iostream>
#include <thread>
#include <vector>
#include <functional>

#include "Consumer.h"
#include "Producer.h"

using namespace std;

void test1(int np, int nc) {
    vector<thread> producer(np), consumer(nc); //生产者消费者线程
    static SharedBuffer bufferSpace(20);        //共享缓冲区
    //线程初始化
    for(int i=0; i<np; ++i) 
        producer[i] = thread(bind(&Producer::Produce, Producer(i, bufferSpace)));
    for(int j=0; j<nc; ++j) 
        consumer[j] = thread(bind(&Consumer::Consume, Consumer(j, bufferSpace)));
    //join线程
    for(auto& thd : producer) thd.join();
    for(auto& thd : consumer) thd.join();
    //唤醒线程
    bufferSpace.notifyNotEmpty();
    bufferSpace.notifyNotFull();
}

int main()
{
    cout << "test1()" << endl;
    test1(100, 100);
    return 0;
}

