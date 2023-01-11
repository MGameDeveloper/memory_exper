
#include "platform.h"

#include "common.h"

int main()
{
	if (!platform_init())
	{
		printf("platform initialization failed\n");
		return -1;
	}

	// engine initialization here

	mem_display_info();

	while (!platform_closing())
	{
		platform_run();

		// engine update here
	}

	printf("application shutting down\n");

	return 0;
}