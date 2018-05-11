#include <cstdlib>
#include <ctime>
#ifdef VXWORKS
#include <taskLib.h>
#include <sysLib.h>
#else
#include <Windows.h>
#include <Winbase.h>
#endif
#include "os.hpp"

void OS::wait(unsigned int ms)
{
#ifdef VXWORKS
	taskDelay(sysClkRateGet()*ms/1000);
#else
    Sleep(ms);
#endif
}

double OS::getTimestamp()
{
    double ret;
#ifdef VXWORKS
    int timestamp;
    timestamp = sysTimestampLock();
    ret = (0.0 + timestamp)/sysTimestampFreq();
#else
    LARGE_INTEGER performanceCount,performanceFrequency;
    QueryPerformanceCounter(&performanceCount);
    QueryPerformanceFrequency(&performanceFrequency);
    ret = (0.0 + performanceCount.QuadPart)/performanceFrequency.QuadPart;
#endif
    return ret;
}

char OS::genVisibleChar()
{
    static int num = 0;
    return '!' + static_cast<char>(num++ % 94);
}

string OS::genVisibleString(int len)
{
    int i;
    char vchar = genVisibleChar();
    string vstr(len,'\0');
    for (i = 0; i < len; i++)
    {
        vstr[i] = vchar;
    }
    return vstr;
}


