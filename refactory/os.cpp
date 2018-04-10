#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "os.hpp"

void OS::wait(unsigned int seconds)
{
    sleep(seconds);
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


