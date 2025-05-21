#include<iostream>
#include<thread>
#include<mutex>

using namespace std;

// if try_lock() is not able to acquire the mutex lock, it would not block the call and moves ahead with next set of lines.
// if a same thread tries to acquire the same lock using try_lock(), the behaviour is undefined.

//  Carefully go through the code to understand...

// The count may never reach 200000 times. due to non blocking nature of the try_lock function.

// This try_lock is the member function of the mutex class.

int counter = 0;
std::mutex m;

void increment(){
    for(int i = 0; i < 100000; i++)
        if(m.try_lock())
            counter++;
        
}