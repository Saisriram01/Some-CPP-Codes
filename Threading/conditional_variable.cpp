// Condition variable allows running threads to wait on some conditions and once those are met the waiting thread can be notified using either 1. notify_one() or 2. notify_all()

// you need mutex to use condition variable.

// steps: 1. acquire the lock using std::unique_lock();
//        2. wait on the condition variable by using wait, wait_for, wait_until.
//        3. then wait for the notify call, check again, act accordingly.



#include<mutex>
#include<thread>
#include<iostream>
#include<condition_variable>

using namespace std;

std::condition_variable cv;
std::mutex m;
int balance = 0;

void add_money(int deposit){
    std::lock_guard<std::mutex> lg(m);
    balance += deposit;
    cv.notify_one(); // In this case it can be notify_all() as well.
}

void withdraw_money(int amt){
    std::unique_lock<std::mutex> u(m);
    cv.wait(u, []{ return (balance >=0) ? true: false;}); // if balance is non-negative the thread can continue to run. but if it is non positive the mutex m that is locked is released by the cv.wait and this awaits a notify call and rechecks again before moving ahead with computation.
    balance -= amt;
}

int main(){
    std::thread t1(add_money, 500);
    std::thread t2(withdraw_money, 500);
    t1.join();
    t2.join();
    return 0;
}