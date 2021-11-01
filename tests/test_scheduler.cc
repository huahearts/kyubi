#include "kyubi/kyubi.h"

static kyubi::Logger::ptr g_logger = KYUBI_LOG_ROOT();

void test_fiber() {
   KYUBI_LOG_INFO(g_logger) << "test in fiber"; 
}
int main(int argc,char** argv) {
    kyubi::Scheduler sc(3,false,"test");
    sc.start();
    sc.stop();
    KYUBI_LOG_INFO(g_logger) << "over";
}
