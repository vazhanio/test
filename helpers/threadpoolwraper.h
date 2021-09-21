#ifndef THREADPOOLWRAPER_H
#define THREADPOOLWRAPER_H
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include<boost/thread.hpp>
class ThreadPoolWraper
{
public:
    explicit ThreadPoolWraper(int batch_size=20);
    bool isFull();
    void addFunction(std::function<void()> f);
    void process();
private:
    boost::asio::thread_pool *pool_m;
    unsigned int thread_count_m;
    int pool_size_m;
    const int batch_size_m;
};

#endif // THREADPOOLWRAPER_H
