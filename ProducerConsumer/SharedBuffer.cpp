#include <iostream>
#include "SharedBuffer.h"
using namespace std;

SharedBuffer::SharedBuffer(int capacity)
    :_bufferCapacity(capacity){
        cout << "缓冲区初始化" << endl;
    }
SharedBuffer::~SharedBuffer(){}

bool SharedBuffer::notempty() {
    return (_buffer.size() > 0);
}
bool SharedBuffer::notfull() {
    return (_buffer.size() < _bufferCapacity);
}

void SharedBuffer::notifyNotEmpty(){
    _notEmpty.notify_all();
}
void SharedBuffer::oneNotEmpty(){
    _notEmpty.notify_one();
}
void SharedBuffer::notifyNotFull(){
    _notFull.notify_all();
}
void SharedBuffer::oneNotFull(){
    _notFull.notify_one();
}
