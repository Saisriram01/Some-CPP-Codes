#include<list>
#include<thread>
#include<mutex>
#include<algorithm>
using namespace std;

std::mutex m;
std::list<int> some_list;

void add_to_list(int a){
    std::lock_guard<std::mutex> guard(m); // unlocks the mutex at the destructor call for the guard variable.
    some_list.push_back(a);
}

bool list_contains(int x){
    std::lock_guard<std::mutex> guard(m);
    return std::find(some_list.begin(), some_list.end(), x) != some_list.end();
}

