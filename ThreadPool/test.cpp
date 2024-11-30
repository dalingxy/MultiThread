#include "ThreadPool.h"

using namespace std;

template<class... Args>
int addFunc(int n, Args... args){
    return n + addFunc(args...);
}
int addFunc(int n){
    return n;
}

int add(int a, int b) {
    return a + b;
}
	
struct structFunc {
	void operator()(int n) {
		cout << "execute void structFunc(" << n << ");" << endl;
	}
};

class A {    
public:
	static void func1(int n = 0) {
		cout << "hello, Afun !" << endl;
	}

	static string func2(int n, string str) {
		string res = "";
        while(n--) res += str;
		return res;
	}
};

int main()
{
    ThreadPool pool;
    
    future<int> t1 = pool.submit(add, 3, 1);
    future<void> t2 = pool.submit(structFunc{}, 7);
    //future<void> t3 = pool.submit(A::func1);
    future<string> t4 = pool.submit(A::func2, 4, "afunc");
    //future<void> t5 = pool.submit([](string s){ cout << s << endl; }, "Submit Lamba Function");

    for(int i=0; i<25; ++i)
        pool.submit(structFunc(), i);
    
    cout << "t1=" << t1.get() << endl;
    cout << "t4=" << t4.get() << endl;

    pool.~ThreadPool();
    return 0;
}

