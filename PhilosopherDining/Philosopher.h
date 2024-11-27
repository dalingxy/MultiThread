#pragma once

#include "Table.h"

class Philosopher
{
public:
    Philosopher(int Pid, Table& table);
    ~Philosopher();
    
    void eat();

private:
    int Pid;
    Table& seatTable; //哲学家就坐的桌子
};

