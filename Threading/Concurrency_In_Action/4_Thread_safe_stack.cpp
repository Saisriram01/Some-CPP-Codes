#include<exception>
#include<thread>
#include<mutex>
#include<stack>
#include<memory>

using namespace std;

struct empty_stack: std::exception
{
    const char* what() const throw();
    // what() returns a C style string with a description of the error.
    // const doesnt allow object modification.
    // throw is saying this function does not throw exceptions.
};

template<typename T>

class threadsafe_stack{
    private:
    std::stack<T> data;
    mutable std::mutex m;
    public:
    threadsafe_stack(){}

    // The copy constructor locks the source object mutex and copies the data
    threadsafe_stack(const threadsafe_stack &source){  //======> (1)
        std::lock_guard<std::mutex> lock(source.m);
        data = source.data;
    }

    threadsafe_stack &operator = (const threadsafe_stack &) = delete;
    void push(T new_val){
        std::lock_guard<std::mutex> lock(m);
        data.push(new_val);
    }

    std::shared_ptr<T> pop(){
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T> (data.pop()));
        data.pop();
        return res;
    }

    void pop(T &val){
        std::lock_guard<std::mutex> lock(m);
        if(data.empty()) throw empty_stack();
        val = data.top();
        data.pop();
    }

    bool empty() const{
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }

};

// Notes:
/*

1. why the copy of the data member happens inside the constructor body instead of using the member initializer list? ==> not being able to lock the mutex on the source may cause race condition. C++ doesn’t allow you to lock another object’s mutex in a member initializer.

*/