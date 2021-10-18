#include "kyubi/kyubi.h"


kyubi::Logger::ptr g_logger = KYUBI_LOG_ROOT();

int count = 0;
kyubi::RWMutex s_mutex;
void func1() {
    KYUBI_LOG_INFO(g_logger) << " name: " << kyubi::Thread::GetName()
                             << " this.name " << kyubi::Thread::GetThis()->getName()
                             << " this.id " << kyubi::GetThreadId()
                             << " this.id: " << kyubi::Thread::GetThis()->getId();
    for (int i = 0;i < 10000;++i) {
        kyubi::RWMutex::WriteLock lock(s_mutex);
        ++count;
    }
}

void func2() {

}

int main(int argc, char** argv) {
    std::vector<kyubi::Thread::ptr> thrs;
    for (int i = 0;i < 5;i++) {
        kyubi::Thread::ptr thr(new kyubi::Thread(&func1,"name_"+std::to_string(i)));
        thrs.push_back(thr);
    }

    for(int i = 0;i < 5;i++) {
        thrs[i]->join();
    }

    KYUBI_LOG_INFO(g_logger) << "thread test end";
    KYUBI_LOG_INFO(g_logger) << "count=" << count;
    return 0;
}