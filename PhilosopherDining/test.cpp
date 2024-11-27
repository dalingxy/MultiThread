#include <iostream>
#include <thread>
#include <functional>

#include "Table.h"
#include "Philosopher.h"

using namespace std;

void test(int n) {
    static Table table(n);
    vector<thread> philosophers;
    for(int i=0; i<n; ++i) {
        philosophers.push_back(
            move(
                thread(
                    bind(&Philosopher::eat, Philosopher(i, table))      
                )
            )
        );
    }

    for(auto& thd : philosophers) thd.join();
}

int main()
{
    int n; 
    while(cin >> n) {
        test(n);
    }
    return 0;
}

