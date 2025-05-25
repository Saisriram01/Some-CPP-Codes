#include<iostream>
#include<mutex>
#include<thread>
#include<chrono>

using namespace std;

// while doing recursion the mutex.lock would cause issues as it was already locked by the thread that is requesting it during recursion.
// std::recursive_mutex resolves this issue. Just remember to unlock as many times as it is locked.

// this is applicable in loops as well.

int a = 0;
std::recursive_mutex rm;

void rec(int val){
    if (!val)
        return;
        rm.lock();
        std::cout<<"recursing for the thread "<<std::this_thread::get_id()<<std::endl;
        rec(val--);
        rm.unlock();

}

int main(){
    std::thread t(rec, 5);
    std::thread p(rec, 10);
    t.join();
    p.join();
    return 0;
}