#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

class SharedBuffer
{
friend class Producer;
friend class Consumer;
public:
    SharedBuffer(int capacity);
    ~SharedBuffer();
    bool notempty();
    bool notfull();
    void notifyNotEmpty();
    void notifyNotFull();
    void oneNotEmpty();
    void oneNotFull();

private:
    queue<int> _buffer;
    int _bufferCapacity;
    mutex _mtx;
    condition_variable _notEmpty;
    condition_variable _notFull;
};

