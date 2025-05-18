#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

//  Mutex and Race conditions.

int common_var = 0; // Common variable for both the threads.
std::mutex m;
void increment(){
    m.lock();
    common_var++; 
    m.unlock();
}

// the call on mutex is a blocking call here.
// all the threads except the one running inside the critical section are left to wait for the lock.


int main()
{
    std::thread t(increment);
    std::thread p(increment);
    t.join();
    p.join();
    std::cout<<common_var<<std::endl;
    return 0;
}

