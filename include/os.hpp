#ifndef OS_H
#define OS_H
#include <fstream>
#include <string>

using std::string;
using std::ofstream;
using std::endl;

class OS
{
public:
	static void wait(unsigned int seconds);
    static void setLogFile(string &file);
    static void addLog(const string &text, bool isNewLine = false);//TODO:实现为模板函数
    static void addLog(const int num, bool isNewLine = false);
    static char randSingleDigit();
    static string randDigitString(int len);

static string logFile;
static bool isLogFileLoad;
static ofstream osf;
};

#endif