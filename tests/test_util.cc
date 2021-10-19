#include "kyubi/kyubi.h"
#include <assert.h>

kyubi::Logger::ptr g_logger = KYUBI_LOG_ROOT();

void test_assert() {
    KYUBI_LOG_INFO(g_logger) << kyubi::BacktraceToString(10);
}

int main(int argc,char** argv) 
{
    test_assert();
    return 0;
}