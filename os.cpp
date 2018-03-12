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
    else OS::addLog("setLogFile failed, log file already loaded!");
}

void OS::addLog(const string &text, bool isNewLine)
{
    if (isLogFileLoad == false)
    {
        osf.open(logFile);
        isLogFileLoad = true;
        OS::addLog("start log ...");
    }
    osf << text;
    if (isNewLine == false) osf << ' ';
    else osf << "\n";

    osf.flush();
}

void OS::addLog(const int num, bool isNewLine)
{
    if (isLogFileLoad == false)
    {
        osf.open(logFile);
        isLogFileLoad = true;
        OS::addLog("start log ...");
    }
    osf << num;
    if (isNewLine == false)
    {
        osf << ' ';
    }
    else
    {
        osf << "\n";
        osf.flush();
    }
}

char OS::randSingleDigit()
{
    srand(clock());
    return '0' + static_cast<char>(rand() % 9);
}

string OS::randDigitString(int len)
{
    int i;
    string str(len + 1,'\0');
    for (i = 0; i < len; i++)
    {
        str[i] = OS::randSingleDigit();
    }
    return str;
}


