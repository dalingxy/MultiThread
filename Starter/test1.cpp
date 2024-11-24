#include <iostream>
#include <thread>
using namespace std;

void process(int n) {
    while(n--) {
        cout << "process()" << endl;
    }
}

class FunctionObject {
public:
    void operator() (int n) const {
        while(n--) 
            cout << "FunctionObject()" << endl;
    }
};

int main() {
    thread t1(process, 5);          // 普通函数
    thread t2(FunctionObject(), 6); // 函数对象
    thread t3([](int n){
        while(n--) cout << "Lambda" << endl;
              }, 3);                // Lambda对象
    t1.join(); // 等待线程完成
    t2.join();
    t3.join();
    return 0;
}
