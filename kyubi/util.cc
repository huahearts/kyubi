#include "util.h"
#include<execinfo.h>
#include "log.h"
#include <unistd.h>
namespace kyubi{

kyubi::Logger::ptr g_logger = KYUBI_LOG_NAME("system");

pid_t GetThreadId() {
    return syscall(SYS_gettid);
}

uint32_t GetFiberId() {
    return 0;
}

void Backtrace(std::vector<std::string>& bt,int size,int skip)
{
    void** array = (void**)malloc((sizeof(void*) * size));
    size_t s = ::backtrace(array,size);
    char** strings = backtrace_symbols(array,s);
    if(strings == NULL) {
        KYUBI_LOG_ERROR(g_logger) << "backtrace_symbols error";
        return;
    }

    for(size_t i = skip;i < s;++i) {
        bt.push_back(strings[i]);
    }

    free(strings);
    free(array);
}

std::string BacktraceToString(int size,int skip,const std::string& prefix)
{
    std::vector<std::string> bt;
    Backtrace(bt,size,skip);
    std::stringstream ss;
    for(size_t i= 0;i < bt.size();++i) {
        ss << prefix << bt[i] << std::endl;
    }
    return ss.str();
}
}

