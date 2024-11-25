#pragma once

#include "SharedBuffer.h"

class Consumer
{
public:
    Consumer(int id, SharedBuffer& sb);
    ~Consumer();
    void Consume();
private:
    int _Cid;
    SharedBuffer& _sharedBuffer;
};

