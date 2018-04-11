#ifndef _OS_H_
#define _OS_H_
#include <string>
using std::string;

class OS
{
public:
	static void wait(unsigned int seconds);
    static char genVisibleChar();
    static string genVisibleString(int len);
};

#endif
