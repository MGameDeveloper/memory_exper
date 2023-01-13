
#include "platform.h"

#include "common.h"


struct example_data
{
	const char* tag = nullptr;
	float       data0 = 0.0f;
	uint32_t    data1 = 0;
	char        data2 = '\0';
};


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

		event_key* k = nullptr;
		while (k = event_get())
		{
			printf("key: %d\n", k->key);
		}
		// engine update here
	}

	platform_deinit();

	return 0;
}