
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
	keyvalue_set(0, ek_w,     -1.f);
	keyvalue_set(0, ek_s,      1.f);
	keyvalue_set(0, ek_up,    -1.f);
	keyvalue_set(0, ek_down,   1.f);
	keyvalue_set(0, ek_a,     -1.f);
	keyvalue_set(0, ek_d,      1.f);
	keyvalue_set(0, ek_left,  -1.f);
	keyvalue_set(0, ek_right,  1.f);

	while (!platform_closing())
	{
		platform_run();
		// engine update here
	}

	platform_deinit();

	return 0;
}