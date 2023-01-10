#include "platform.h"

#include "win32/win32.h"

bool platform_init()
{
#ifdef WIN32
	return win32_init();
#endif
}

void platform_run()
{
#ifdef WIN32
	win32_run();
#endif
}

bool platform_closing()
{
#ifdef WIN32
	return win32_closing();
#endif
}