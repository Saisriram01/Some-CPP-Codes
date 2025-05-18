#include<iostream>
#include<thread>

// There are 5 different ways we can create threads in c++11 using callable objects.

// 1. Function Pointer

// Note: If we are creating multiple threads at the same time, it doesnt gurantee which will start first.
    //  eg: std::thread t(func,10);
    //      std::thread p(func,15);

// bool func(int a){
//     return a & 1 == 0;
// }

// void main(){
//     std::thread t1(func,10);
// }

// 2. Lambda Function
// int main(){
//     auto func = [](int a){
//         return a & 1 ==0;
//     };
//     std::thread p(func, 10); // we can create a thread and pass on a lambda just like a function.
//     std::thread t([](int x){ // or we can also ingest a lambda function directly into a thread creation.
//         return x & 1 == 0;
//     }, 10);
// }


// 3. Using Functor (Function Object)

// class base{
//     public:
//     bool operator () (int x){
//         return x & 1 == 0;
//     }
// };

// int main(){
//     std::thread t((base()), 10); // Most vexing parse can cause issue, so change it to std::thread t(base{}, 10); source chatGPT
//     return 0;
// }


// 4. Non-Static member function

// class base{
//     public:
//     void run(int x){
//         while (x-- > 0)
//             std::cout<<x<<std::endl;
//     }
// };

// int main(){
//     base b;
//     std::thread t(&base::run, &b, 10); // we have to indicate  to which object does this call to run belongs to.
//     t.join();
//     return 0;
// }


// 5. Static Member function

class base{
    public:
    static void run(int x){
        while(x-->0)
            std::cout<<x<<std::endl;
    }
};

int main(){
    base b;
    std::thread t(&base::run, 10);
    t.join();
    return 0;
}