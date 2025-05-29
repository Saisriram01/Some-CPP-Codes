#include<iostream>
#include<mutex>
using namespace std;

class s;

void swap(s &a, s &b);

class x{
    private:
        s a;
        std::mutex m;

    public:
        x(s const & d): s(d){}
        friend void swap(x &b, x &c){
            if(&b == &c)
                return;
            std::lock(b.m, c.m);
            std::lock_guard<std::mutex> lock_b(b.m, std::adopt_lock); 
            std::lock_guard<std::mutex> lock_c(c.m, std::adopt_lock);
            // std::adopt_lock()  is a special tag type used in C++ to tell a std::lock_guard or std::unique_lock that the mutex is already locked and it should adopt ownership without locking again.

            swap(b.a, c.a);
        }
};