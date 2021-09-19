#ifndef WATCHER_H
#define WATCHER_H

#include <chrono>
#include <string>
class Watcher{
public:

    Watcher(std::string title=""):title_m(title){

    }
    void start()
    {
        start_m=std::chrono::high_resolution_clock::now();
    }
    void stop() {
        miliseconds_m+=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start_m).count();
    }
    auto release()
    {
        return title_m+"-> "+std::to_string( miliseconds_m);
    }

   std::string title_m;
   std::chrono::time_point<std::chrono::high_resolution_clock> start_m;
   std::chrono::time_point<std::chrono::high_resolution_clock> summary_time_m;
   double miliseconds_m=0;
};

#endif // WATCHER_H
