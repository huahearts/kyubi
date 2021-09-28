#ifndef __UTIL_H__
#define __UTIL_H__
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
namespace kyubi {
pid_t GetThreadId();
uint32_t GetFiberId();

}
#endif