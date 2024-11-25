#pragma once

#include "SharedBuffer.h"

class Producer
{
public:
    Producer(int id, SharedBuffer &sb);
    ~Producer();
    void Produce();

private:
    SharedBuffer& _sharedBuffer;
    int _Pid;
};

