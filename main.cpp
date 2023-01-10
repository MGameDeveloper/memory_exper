#include <stdio.h>

#include "platform.h"

#include "utils/Memory.h"
#include "utils/Containers/Stack.h"

struct data_s
{
	const char* name = nullptr;
	uint32_t value = 0;
};

int main()
{
	if (!platform_init())
	{
		printf("platform initialization failed\n");
		return -1;
	}

	data_s d0 = { "d0", 1 };

	{
		Stack* dishes = (Stack*)stack_create("stack_dishes", 2, sizeof(data_s));
		stack_add(dishes, &d0);
	}

	Stack* dishes_by_name = (Stack*)mem_get("stack_dishes");
	if (dishes_by_name)
	{
		data_s d1 = { "d1", 2 };
		stack_add(dishes_by_name, &d1);
	}
	mem_display_info();

	stack_destroy(&dishes_by_name);

	mem_display_info();
	
	// engine initialization here

	while (!platform_closing())
	{
		platform_run();

		// engine update here
	}

	printf("application shutting down\n");

	return 0;
}