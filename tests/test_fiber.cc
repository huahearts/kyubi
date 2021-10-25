#include "kyubi/kyubi.h"

kyubi::Logger::ptr g_logger = KYUBI_LOG_ROOT();

void run_in_fiber(){
    KYUBI_LOG_INFO(g_logger) << "run_in_fiber begin";
    kyubi::Fiber::GetThis()->swapOut();
    KYUBI_LOG_INFO(g_logger) << "run_in_fiber end";
}

int main(int argc,char** argv){
    KYUBI_LOG_INFO(g_logger) << "main begin";
    kyubi::Fiber::ptr fiber(new kyubi::Fiber(run_in_fiber));
    fiber->swapIn();
    KYUBI_LOG_INFO(g_logger) << "main after swapIn";
    fiber->swapIn();
}