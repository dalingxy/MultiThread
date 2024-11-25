#include <iostream>
#include <cstdlib>
#include <ctime>
#include <functional>

#include "Producer.h"

using namespace std;

Producer::Producer(int id, SharedBuffer &sb)
    :_Pid(id)
    ,_sharedBuffer(sb){

    }
Producer::~Producer(){}

void Producer::Produce() {
    srand(time(NULL));
    int produceNumber = rand() % 100;

    unique_lock<mutex> lock(_sharedBuffer._mtx);
    _sharedBuffer._notFull.wait(lock, bind(&SharedBuffer::notfull, &_sharedBuffer));
    _sharedBuffer._buffer.push(produceNumber);
    cout << "Producer_" << _Pid << " 写入缓冲区：" 
         << produceNumber << endl;

    _sharedBuffer.oneNotEmpty();
}
