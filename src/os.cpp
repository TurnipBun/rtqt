#include <cstdlib>
#include <ctime>
#ifdef VXWORKS
#else
#include <Windows.h>
#endif
#include "os.hpp"

void OS::wait(unsigned int ms)
{
#ifdef VXWORKS
#else
    Sleep(ms);
#endif
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


