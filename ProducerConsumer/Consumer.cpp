#include <iostream>
#include <functional>

#include "Consumer.h"

using namespace std;

Consumer::Consumer(int id, SharedBuffer& sb)
    :_Cid(id), _sharedBuffer(sb){

    }
Consumer::~Consumer(){}

void Consumer::Consume() {
    unique_lock<mutex> lock(_sharedBuffer._mtx);
    _sharedBuffer._notEmpty.wait(lock, bind(&SharedBuffer::notempty, &_sharedBuffer));
    
    int getNumber = _sharedBuffer._buffer.front();
    _sharedBuffer._buffer.pop();
    cout << "Consumer_" << _Cid << " 读取缓冲区："
         << getNumber << endl;

    _sharedBuffer.oneNotFull();
}
