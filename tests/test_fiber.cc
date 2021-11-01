#include "kyubi/kyubi.h"

kyubi::Logger::ptr g_logger = KYUBI_LOG_ROOT();

void run_in_fiber(){
    KYUBI_LOG_INFO(g_logger) << "run_in_fiber begin";
    kyubi::Fiber::GetThis()->swapOut();
    KYUBI_LOG_INFO(g_logger) << "run_in_fiber end";
}

void test_fiber() {
    KYUBI_LOG_INFO(g_logger) << "main begin";
    kyubi::Fiber::ptr fiber(new kyubi::Fiber(run_in_fiber));
    fiber->swapIn();
    KYUBI_LOG_INFO(g_logger) << "main after swapIn";
    fiber->swapIn();
}

int main(int argc,char** argv){
    kyubi::Thread::SetName("main");
    std::vector<kyubi::Thread::ptr> thrs;
    for(int i = 0;i < 3;i++) {
        thrs.push_back(kyubi::Thread::ptr(new kyubi::Thread(&test_fiber,"name_" + std::to_string(i))));
    }

    for(auto i : thrs) {
        i->join();
    }
    return 0;
}