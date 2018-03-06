#ifdef VXWORKS
#endif

#ifdef MINGW32
#endif


#include <unistd.h>
#include "os.hpp"

void OS::wait(unsigned int seconds)
{
	sleep(seconds);
}