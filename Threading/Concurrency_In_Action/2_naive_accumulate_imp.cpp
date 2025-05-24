#include<thread>
using namespace std;

// this is a naive implementation of the std::accumulate function as presented in
// Listing 2.8 

template<typename Iterator, typename T>
struct accumulate_block{
    void operator()(Iterator first, Iterator last, T &result){
        result = std::accumulate(first, last, result);
    }
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init){
    unsigned long cast length = std::distance(first, last); // distance function returns the no. of elements between the two iterators provided. 
    if(!length)
        return init;
    unsigned long const min_per_thread = 25;
    unsigned long const max_threads = (length + min_per_thread - 1)/min_per_thread;
    unsigned long const hardware_threads = std::thread::hardware_concurrency();

    unsigned long const num_threads = std::min(hardware_threads != 0? hardware_threads:4,max_threads); // this is to avoid what is called oversubscription. Otherwise the context_switching will degrade the performance.

    unsigned long const block_size = length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads - 1); // one less thread because we are already running in one. The current thread will also do the work (the accumulate call after the for loop).

    Iterator block_start= first;
    for(unsigned long i = 0; i < num_threads - 1; i++){
        Iterator block_end = block_start;
        std::advance(block_end, block_size); // function to move the iterator forward or backward by the length specified.

        threads[i] = std::thread(accumulate_block<Iterator, T>(), block_start, block_end, std::ref(results[i]));
        block_start = block_end;
    } 
    accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

    return std:accumulate(results.begin(), results.end(),init);
}

// Things to note:
/*
    since the thread constructor copies the values and we had a reference variable to accumulate_block function, we use std::ref(results[i]);

*/