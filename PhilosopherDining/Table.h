#pragma once

#include <vector>
#include <mutex>
#include <memory>

using namespace std;

//这是哲学家们就餐的桌子
class Table
{
public:
    Table(int n);
    ~Table();

    // 禁止拷贝构造与赋值
    Table(const Table&) = delete;
    Table& operator=(const Table&) = delete;

    mutex& getMutex(size_t Mid);
    int getNum();

private:
    int forkNum;              //筷子数量（ =哲学家数量 ）
    vector<unique_ptr<mutex>> forkMutexs; 
                              //每个筷子只能被一位哲学家拿着
};

