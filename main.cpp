
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

static float player_y_pos = 0.0f;

// Axis handlers
void move_forward(float invalue)
{
	//printf("forward: %.2f\n", invalue);
	player_y_pos += invalue;
}
void move_sideward(float invalue)
{
	//printf("sideward: %.2f\n", invalue);
	player_y_pos += invalue;
}

// Action handlers
void dodge()
{
	printf("Dodge\n");
}
void useitem()
{
	printf("Useitem\n");
}
void attack()
{
	printf("Attack\n");
}
void shield()
{
	printf("Shield\n");
}

int main()
{
	if (!platform_init())
	{
		printf("platform initialization failed\n");
		return -1;
	}

	// engine initialization here
	inputlayout_init(0, actionid_count);

	// actions bindings
	bind_action_msg(einputuser_0, ek_d, keystate_pressed, actionid_dodge);
	bind_action_msg(einputuser_0, ek_z, keystate_pressed, actionid_useitem);
	bind_action_msg(einputuser_0, ek_f, keystate_pressed, actionid_attack);
	bind_action_msg(einputuser_0, ek_x, keystate_pressed, actionid_shield);

	// axes bindings
	bind_axis_msg(einputuser_0, ek_up,    axisid_forward,  -1.f);
	bind_axis_msg(einputuser_0, ek_down,  axisid_forward,   1.f);
	bind_axis_msg(einputuser_0, ek_w,     axisid_forward,  -1.f);
	bind_axis_msg(einputuser_0, ek_s,     axisid_forward,   1.f);
	bind_axis_msg(einputuser_0, ek_left,  axisid_sideward, -1.f);
	bind_axis_msg(einputuser_0, ek_right, axisid_sideward,  1.f);
	bind_axis_msg(einputuser_0, ek_a,     axisid_sideward, -1.f);
	bind_axis_msg(einputuser_0, ek_d,     axisid_sideward,  1.f);

	// msg handlers
	bind_action_handler(einputuser_0, actionid_dodge,   dodge);
	bind_action_handler(einputuser_0, actionid_useitem, useitem);
	bind_action_handler(einputuser_0, actionid_attack,  attack);
	bind_action_handler(einputuser_0, actionid_shield,  shield);
	
	bind_axis_handler(einputuser_0, axisid_forward,  move_forward);
	bind_axis_handler(einputuser_0, axisid_sideward, move_sideward);

	mem_display_info();

	while (!platform_closing())
	{
		platform_run();

		// engine update here
		printf("player_y_pos: %.2f\n", player_y_pos);
	}

	platform_deinit();

	return 0;
}