#ifndef __KYUBI_MACRO_H__
#define __KYUBI_MACRO_H__
#include <string.h>
#include <assert.h>
#include "util.h"

#define KYUBI_ASSERT(x) \
    if(!(x)) {\
        KYUBI_LOG_ERROR(KYUBI_LOG_ROOT()) << "ASSERTION:" #x\
            << "\nbacktrace:\n"\
            << kyubi::BacktraceToString(100,2,"     ");\
        assert(x);\
    }

#define KYUBI_ASSERT2(x,w) \
    if(!(x)) {\
        KYUBI_LOG_ERROR(KYUBI_LOG_ROOT()) << "ASSERTION:" #x\
            << "\n" << w\
            << "\nbacktrace:\n"\
            << kyubi::BacktraceToString(100,2,"     ");\
        assert(x);\
    }
#endif