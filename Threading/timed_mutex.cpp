#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>

using namespace std;

// std::timed_mutex is blocked till the timeout_time or the lock is aquired and returns true if success otherwise false.
// try_lock_for()
// try_lock_until()

int amt = 0;
std::timed_mutex m;

void increment(){
    if(m.try_lock_for(std::chrono::seconds(2))){
        ++amt;
        std::cout<<"Thread with id "<< std::this_thread::get_id()<<" entered for incrementing."<<std::endl;
        std:this_thread::sleep_for(std::chrono::seconds(3));
        m.unlock();
    }
    else{
        std::cout<<"Thread with id "<< std::this_thread::get_id()<<" could not perform the incrementing."<<std::endl;
    }

}

// similarly for try_lock_until --> we can specify time for example:
// auto curr_time = std::chrono::steady_clock::now();
// if(m.try_lock_until(now + std::chrono::seconds(2)))---> wait for two seconds from now...did not make much sense from the example.

int main(){

    std::thread t(increment);
    std::thread p(increment);
    t.join();
    p.join();
    return 0;
}