#include<thread>
#include<iostream>
using namespace std;

class thread_guard{
    std::thread &t;
    public:
    explicit thread_guard(std::thread &t1): t(t1){} // explicit keyword is used to avoid any implicit type conversions for the parameters.
    ~thread_guard(){
        if(t.joinable())
            t.join();
    }

    thread_guard(thread_guard const &) = delete;
    thread_guard & operator = (thread_guard const &) = delete;
    // deleting the copy constructor and assignment operator to avoid any issues.

};

struct func{
    int &i;
    func(int &i_):i(i_){}
    void operator()(){
        for(unsigned j = 0; j<10000000; ++j){
            std::cout<<j<<std::endl;
        }
    }
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach();
}

