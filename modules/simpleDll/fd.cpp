#include "fd.h"

void foo_dll(int i)
{
    std::cerr<<"From DLL: i->"<<std::to_string(i)<<" :)))";
    return;
}

void bar(const std::string s){
    std::cerr<<"from bar->"<<s<<" ^_^\n";
}

int foo_int()
{
    return 5;
}
