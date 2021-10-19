#include "kyubi/kyubi.h"


kyubi::Logger::ptr g_logger = KYUBI_LOG_ROOT();

int count = 0;
//kyubi::RWMutex s_mutex;
kyubi::Mutex s_mutex;
void func1() {
    KYUBI_LOG_INFO(g_logger) << " name: " << kyubi::Thread::GetName()
                             << " this.name " << kyubi::Thread::GetThis()->getName()
                             << " this.id " << kyubi::GetThreadId()
                             << " this.id: " << kyubi::Thread::GetThis()->getId();
    for (int i = 0;i < 10000;++i) {
        //kyubi::RWMutex::WriteLock lock(s_mutex);

        kyubi::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void func2() {
    while(true) {
        KYUBI_LOG_INFO(g_logger) << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    }
    
}

void func3() {
    while(true) {
        KYUBI_LOG_INFO(g_logger) << "===============================";
    }
}

int main(int argc, char** argv) {
    KYUBI_LOG_INFO(g_logger) << "thread test begin";
    std::vector<kyubi::Thread::ptr> thrs;
    for (int i = 0;i < 2;i++) {
        kyubi::Thread::ptr thr(new kyubi::Thread(&func2,"name_"+std::to_string(i * 2)));

        kyubi::Thread::ptr thr2(new kyubi::Thread(&func3,"name_"+std::to_string(i * 2+1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }

    for(size_t i = 0;i < thrs.size();i++) {
        thrs[i]->join();
    }


    
    KYUBI_LOG_INFO(g_logger) << "thread test end";
    KYUBI_LOG_INFO(g_logger) << "count=" << count;

    kyubi::Config::Visit([](kyubi::ConfigVarBase::ptr var){
        KYUBI_LOG_INFO(g_logger) <<" name=";
    })
    return 0;
}