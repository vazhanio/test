#include "threadpoolwraper.h"

ThreadPoolWraper::ThreadPoolWraper(int batch_size):pool_size_m(0),
    batch_size_m(batch_size),
    thread_count_m(boost::thread::physical_concurrency())
{
    pool_m=new boost::asio::thread_pool(thread_count_m);
}

bool ThreadPoolWraper::isFull()
{
    return pool_size_m == batch_size_m;
}

void ThreadPoolWraper::addFunction(std::function<void ()> f)
{
    boost::asio::post(*pool_m,f);
    pool_size_m++;
}

void ThreadPoolWraper::process()
{
    pool_m->join();
    pool_size_m=0;
    delete  pool_m;
    pool_m=new boost::asio::thread_pool(thread_count_m);
}
