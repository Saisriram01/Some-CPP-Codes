// This is an example code explaining std::try_lock().
// To Note: this is different from mutex.try_lock();
// try_lock(m1,m2,m3,m4....m_n) tries to lock all the mutexes at the same time.
    //  if successful, then -1 is returned.
    // if not the index of the failed mutex is returned (zero_ordering).

// if a mutex fails, the running of the other successful ones are interrupted as well.
// if a call to try_lock results in an exception, unlock is called for any locked objects before throwing.

#include<mutex>
#include<iostream>
#include<thread>
#include<chrono>

using namespace std;
int x = 0, y = 0;
std::mutex m1,m2;

void increment(int &xory, std::mutex &m, const char* desc){
    for(int i= 0; i <5 ;i++)
    {
        m.lock();
        std::cout<< desc<< xory++ <<std::endl;
        m.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void consume(){
    int usecount = 5;
    int xplusy = 0;
    while(1){
        int lockresult = std::try_lock(m1, m2);
        if(lockresult == -1){
            if(x!=0 && y!=0){
                usecount--;
                xplusy += x+y;
                x = 0;
                y = 0;
                std::cout<<xplusy<<std::endl;
            }
        m1.unlock();
        m2.unlock();
        if(!usecount)
            break;
        }
    }
}

int main(){
    
    std::thread t1(increment, std::ref(x), std::ref(m1),"X = ");
    std::thread t2(increment, std::ref(y),std::ref( m2), "Y = ");
    std::thread t3(consume);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}