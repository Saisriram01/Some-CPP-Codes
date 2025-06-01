// std::lock() is used to lock multiple mutexes at the same time.
//  std::lock() internally uses a strategy to avoid deadlocks by carefully arranging the lock acquisition order.

// Why You Must Use adopt_lock Afterwards
// Because std::lock() has already locked the mutexes, you must wrap them like:

// std::lock() is a blocking call.

// It waits until it can acquire all mutexes atomically.
    // if it can not acquire a lock on a mutex, it release all the previously acquired mutexes.


#include<iostream>
#include<thread>
#include<mutex>

std::mutex m1,m2;

void task_a(){
    while(1){
        std::lock(m1,m2);
        std::lock_guard<std::mutex> lock1(m1, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);
        std::cout<<"task 1";
    }
}

void task_b(){
    while(1){
        std::lock(m1,m2);
        std::lock_guard<std::mutex> lock1(m1, std::adopt_lock);
        std::lock_guard<std::mutex> lock2(m2, std::adopt_lock);
        std::cout<<"task 1";
    }
}

int main(){
    std::thread t1(task_a);
    std::thread t2(task_b);

    t1.join();
    t2.join();
    return 0;
}