#include "input_binding_test.h"

#include "../../common.h"


enum egamecmd
{
	egc_unknown,

	egc_forward,
	egc_sideward,

	egc_dodge,
	egc_useitem,
	egc_attack,

	egc_shield,

	egc_count
};


void move_forward(float invalue)
{
	printf("forward: %.2f\n", invalue);
}
void move_sideward(float invalue)
{
	printf("sideward: %.2f\n", invalue);

}
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


bool player_one_init_input() 
{
	user_input_map* game = create_user_input_map();
	if (!game)
		return false;

	// actions bindings
	bind_action_msg(game, ek_e,        keystate_repeated, egc_dodge);
	bind_action_msg(game, ek_r,        keystate_repeated, egc_useitem);
	bind_action_msg(game, ek_triangle, keystate_pressed,  egc_dodge);
	bind_action_msg(game, ek_cross,    keystate_repeated, egc_useitem);
	bind_action_msg(game, ek_f,        keystate_pressed,  egc_attack);
	bind_action_msg(game, ek_x,        keystate_pressed,  egc_shield);

	// axes bindings
	bind_axis_msg(game, ek_up,           egc_forward,  -1.f);
	bind_axis_msg(game, ek_down,         egc_forward,   1.f);
	bind_axis_msg(game, ek_w,            egc_forward,  -1.f);
	bind_axis_msg(game, ek_s,            egc_forward,   1.f);
	bind_axis_msg(game, ek_left,         egc_sideward, -1.f);
	bind_axis_msg(game, ek_right,        egc_sideward,  1.f);
	bind_axis_msg(game, ek_a,            egc_sideward, -1.f);
	bind_axis_msg(game, ek_d,            egc_sideward,  1.f);
	bind_axis_msg(game, ek_lanalogup,    egc_forward,  -1.f);
	bind_axis_msg(game, ek_lanalogdown,  egc_forward,   1.f);
	bind_axis_msg(game, ek_lanalogleft,  egc_sideward, -1.f);
	bind_axis_msg(game, ek_lanalogright, egc_sideward,  1.f);

	// msg handlers
	bind_action_handler(game, egc_dodge,   dodge);
	bind_action_handler(game, egc_useitem, useitem);
	bind_action_handler(game, egc_attack,  attack);
	bind_action_handler(game, egc_shield,  shield);

	bind_axis_handler(game, egc_forward,  move_forward);
	bind_axis_handler(game, egc_sideward, move_sideward);

	if (!push_input_map(einputuser_0, game))
		return false;

	return true;
}


