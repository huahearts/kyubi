#ifndef __UTIL_H__
#define __UTIL_H__
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string>
#include <vector>
namespace kyubi {
pid_t GetThreadId();
uint32_t GetFiberId();
void Backtrace(std::vector<std::string>& bt,int size,int skip = 1);

std::string BacktraceToString(int size = 64,int skip = 2,const std::string& prefix = "");
}
#endif