#include <stdio.h>

#include "platform.h"

#include "utils/Memory.h"
#include "utils/Containers/Stack.h"

int main()
{
	if (!platform_init())
	{
		printf("platform initialization failed\n");
		return -1;
	}

	// engine initialization here

	while (!platform_closing())
	{
		platform_run();

		// engine update here
	}

	printf("application shutting down\n");

	return 0;
}