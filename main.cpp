
#include "core/platform/platform.h"

#include "common.h"

#include "tests/input/input_binding_test.h"


int main()
{
	if (!platform_init())
	{
		printf("platform initialization failed\n");
		return -1;
	}

	// engine initialization here
	if (!player_one_init_input())
	{
		printf("player one initialization failed.\n");
		return -1;
	}

	mem_display_info();

	while (!platform_closing())
	{
		time_begin();

		platform_run();


		time_end();
	}

	platform_deinit();

	return 0;
}

