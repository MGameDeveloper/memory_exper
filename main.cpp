
#include "platform.h"

#include "common.h"

enum eactionid
{
	actionid_unknown,

	axisid_forward,
	axisid_sideward,
	actionid_dodge,
	actionid_forward,
	actionid_sideward,
	actionid_useitem,
	actionid_attack,
	actionid_shield,

	actionid_count
};


void axis_handler(float invalue)
{
	printf("forward: %.2f\n", invalue);
}

void action_handler()
{
	printf("actions.\n");
}

int main()
{
	if (!platform_init())
	{
		printf("platform initialization failed\n");
		return -1;
	}

	// engine initialization here

	// actions bindings
	bind_action_msg(einputuser_0, ek_d, keystate_pressed, actionid_dodge,   emodkey_unknown);
	bind_action_msg(einputuser_0, ek_e, keystate_pressed, actionid_useitem);
	bind_action_msg(einputuser_0, ek_f, keystate_pressed, actionid_attack);
	bind_action_msg(einputuser_0, ek_x, keystate_pressed, actionid_shield);

	// axes bindings
	bind_axis_msg(einputuser_0, ek_up,    axisid_forward,  -1.f);
	bind_axis_msg(einputuser_0, ek_down,  axisid_forward,   1.f);
	bind_axis_msg(einputuser_0, ek_left,  axisid_sideward, -1.f);
	bind_axis_msg(einputuser_0, ek_right, axisid_sideward,  1.f);

	// msg handlers
	bind_action_handler(actionid_useitem, action_handler);
	bind_axis_handler  (axisid_forward,   axis_handler);

	while (!platform_closing())
	{
		platform_run();
		// engine update here
	}

	platform_deinit();

	return 0;
}