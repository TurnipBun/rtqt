#ifdef VXWORKS
#endif

#ifdef MINGW32
#endif
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include "os.hpp"

string OS::logFile = "rtqt.txt";
bool OS::isLogFileLoad = false;
ofstream OS::osf;

void OS::wait(unsigned int seconds)
{
	sleep(seconds);
}

void OS::setLogFile(string &file)
{
    if (isLogFileLoad == false) logFile = file;
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
    string vstr(len + 1,'\0');
    for (i = 0; i < len; i++)
    {
        vstr[i] = vchar;
    }
    return vstr;
}


