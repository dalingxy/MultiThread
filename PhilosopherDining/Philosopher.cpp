#include <iostream>
#include <chrono>
#include <thread>

#include "Philosopher.h"

using namespace std;

Philosopher::Philosopher(int Pid, Table& table)
    :Pid(Pid), seatTable(table) {

}

Philosopher::~Philosopher() {}

void Philosopher::eat() {
    //Pid号哲学家的左右筷子
    int leftFork = Pid, rightFork = (Pid+1)%seatTable.getNum();
    
    lock(seatTable.getMutex(leftFork), seatTable.getMutex(rightFork));
    unique_lock<mutex> llock(seatTable.getMutex(leftFork), adopt_lock);
    unique_lock<mutex> rlock(seatTable.getMutex(rightFork),adopt_lock);
    
    cout << "Philosopher_" << Pid << " begins to eat..." << endl;
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Philosopher_" << Pid << " ends dining." << endl;
}
