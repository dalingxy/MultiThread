#include <iostream>

#include "Table.h"

using namespace std;

Table::Table(int n) :forkNum(n) {
    for(int i=0; i<n; ++i) 
        forkMutexs.push_back(make_unique<mutex>());
    
    cout << "There are " << n << " forks and philosophers around the table." << endl;
}

Table::~Table() {}

int Table::getNum() {
    return forkNum;
}

mutex& Table::getMutex(size_t Mid) {
    return *forkMutexs[Mid];
}
