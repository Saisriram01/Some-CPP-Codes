// These are used for thread synchronization and communication, for passing values from one thread to another.

// promise<T> is a way to set a value that will be available in the future.
// future<T> is a way to get that value when it is ready(possibly waiting for it)

//These two often go hand in hand.
// one thread produces a value via promise.
// Another thread consumes that value via future.

#include<iostream>
#include<thread>
#include<future>

void func(std::promise<int> p){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    p.set_value(234);
}

int main(){
    std::promise<int> p;
    std::future<int> f = p.get_future();
    
    std::thread t(func, std::move(p));
    // to note: promise is non-copyable just like unique_ptr or mutex. Once you've moved p, it becomes empty/invalid in the original thread. If you try to call p.set_value() afterward in main(), you’ll get undefined behavior.



    std::cout<<"Value passed on from thread: "<< f.get()<<std::endl;

    t.join();
    return 0;
}