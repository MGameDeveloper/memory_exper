
#include "core/platform/platform.h"

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

static float player_y_pos = 50.f;
static float player_y_vel = 0.0f;

// Axis handlers
void move_forward(float invalue)
{
	printf("forward: %.2f\n", invalue);
	//player_y_vel += invalue;
}
void move_sideward(float invalue)
{
	printf("sideward: %.2f\n", invalue);
	//player_y_vel += invalue;
}

// Action handlers
void dodge()
{
	printf("Dodge\n");
	controller_vibrate_start(einputuser_0, 32000, 16000);
}

void useitem()
{
	printf("Useitem\n");
	controller_vibrate_end(einputuser_0);
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
	//inputlayout_init(0, actionid_count);
	 
	user_input_map* game = create_user_input_map();
	if (!game)
		return -1;

	// actions bindings
	bind_action_msg(game, ek_e, keystate_repeated, actionid_dodge);
	bind_action_msg(game, ek_r, keystate_repeated, actionid_useitem);
	bind_action_msg(game, ek_triangle, keystate_pressed, actionid_dodge);
	bind_action_msg(game, ek_cross, keystate_repeated, actionid_useitem);
	bind_action_msg(game, ek_f, keystate_pressed, actionid_attack);
	bind_action_msg(game, ek_x, keystate_pressed, actionid_shield);

	// axes bindings
	bind_axis_msg(game, ek_up,    axisid_forward,  -1.f);
	bind_axis_msg(game, ek_down,  axisid_forward,   1.f);
	bind_axis_msg(game, ek_w,     axisid_forward,  -1.f);
	bind_axis_msg(game, ek_s,     axisid_forward,   1.f);
	bind_axis_msg(game, ek_left,  axisid_sideward, -1.f);
	bind_axis_msg(game, ek_right, axisid_sideward,  1.f);
	bind_axis_msg(game, ek_a,     axisid_sideward, -1.f);
	bind_axis_msg(game, ek_d,     axisid_sideward,  1.f);
	bind_axis_msg(game, ek_lanalogup,    axisid_forward,  -1.f);
	bind_axis_msg(game, ek_lanalogdown,  axisid_forward,   1.f);
	bind_axis_msg(game, ek_lanalogleft,  axisid_sideward, -1.f);
	bind_axis_msg(game, ek_lanalogright, axisid_sideward,  1.f);

	// msg handlers
	bind_action_handler(game, actionid_dodge,   dodge);
	bind_action_handler(game, actionid_useitem, useitem);
	bind_action_handler(game, actionid_attack,  attack);
	bind_action_handler(game, actionid_shield,  shield);
	
	bind_axis_handler(game, axisid_forward,  move_forward);
	bind_axis_handler(game, axisid_sideward, move_sideward);

	push_input_map(einputuser_0, game);

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

