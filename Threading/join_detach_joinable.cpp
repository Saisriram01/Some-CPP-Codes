#include<iostream>
#include<chrono>
#include<thread>
using namespace std;
// 1. Join notes:
//      Once a thread is started we wait for this thread to finish by calling join() on thread object.
//      Having t.join() twice leads to termination of the program with some error.
//      To be sure, we can check for the joinability of the thread before actually joining it. by using joining function.

void func(int a)
{
    while(a-->0)
        std::cout<<a<<std::endl;
    std::this_thread::sleep_for(chrono::seconds(3));
}
int main()
{   
    std::thread t(func, 10);
    std::cout<<"inside main";
    if(t.joinable())
        t.join();
    std::cout<<"After the join statement";
    return 0;
}

// 2. DETACH:
//  This is to detach the newly created thread from the parent thread.
//  the parent thread would not wait for the child thread. so main can terminate if the child thread has not finished. 
// the detached thread execution is suspended, in case of main function terminating.
//  similar to the above case of double join, we can not do double detach. the check for this again is joinable() before detaching.

// IMPORTANT:
//  there is a mistake in the ThreadCreation.cpp program:
//  Every thread call should have a join() or detach(), otherwise the destructor will terminate the program.
//  The moment a thread is created, it is marked as joinable, and once it is either joined or detached, it is marked as non-joinable.

/*
 If you do neither join() nor detach():
When the std::thread object goes out of scope (e.g., at the end of a function like main()), 
it checks if the thread is still joinable using .joinable().

If it is joinable and you did not join() or detach() it,

The ~thread() destructor will throw std::terminate(), which will crash your program.
*/