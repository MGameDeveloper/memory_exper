#include "input_binding_test.h"

#include "../../common.h"

enum ewalkcmd
{
	// movement cmds
	ewc_move_forward,
	ewc_move_right,
	ewc_run,

	// positions cmds
	ewc_jump,
	ewc_crouch,
	ewc_lay,

	// fighting cmds
	ewc_attack,
	ewc_next_weapon,
	ewc_prev_weapon,

	ewc_change_camera,

	ewc_count
};

enum ejetcmd
{
	// movements cmds
	ejc_accelerate,
	ejc_decelerate,
	ejc_roll_right,
	ejc_go_up,
	ejc_turn_right,
	ejc_turn_left,
	ejc_toggle_wheels,

	// fighting cmds
	ejc_fire,
	ejc_lunch_missle,
	ejc_lunch_flares,

	egc_change_camera,

	ejc_count,
};

enum eswimcmd
{
	// movement cmds
	esc_move_forward,
	esc_move_right,
	esc_swim_hard,
	esc_dive,

	esc_change_camera,

	esc_count,
};

enum evehiclecmd
{
	// movement cmds
	evc_accelrate,
	evc_reverse,
	evc_break,
	evc_turn_right,

	// fighting cmds
	evc_aim_right,
	evc_aim_left,
	evc_attack,

	evc_horn,
	evc_change_camera,

	evc_count,
};

enum emenucmd
{
	emc_up,
	emc_down,
	emc_right,
	emc_left,
	emc_select,
	emc_back,

	emc_count,
};

enum einputmaptype
{
	eim_unknown,

	eim_walk,
	eim_swim,
	eim_menu,
	eim_vehicle,
	eim_jet,

	eim_count
};



void init_walk_input_map(user_input_map* input_map)
{
	if (input_map)
		return;

	input_map = create_user_input_map();
	if (!input_map)
		return;

	bind_axis_msg(input_map,   ek_lanalogup,    ewc_move_forward);
	bind_axis_msg(input_map,   ek_lanalogright, ewc_move_right);
	bind_action_msg(input_map, ek_L3,           keystate_pressed, ewc_run);

	bind_action_msg(input_map, ek_cross,  keystate_pressed,  ewc_jump);
	bind_action_msg(input_map, ek_circle, keystate_pressed,  ewc_crouch);
	bind_action_msg(input_map, ek_circle, keystate_repeated, ewc_lay);
	bind_action_msg(input_map, ek_square, keystate_pressed,  ewc_attack);
	bind_action_msg(input_map, ek_R1,     keystate_pressed,  ewc_next_weapon);
	bind_action_msg(input_map, ek_L1,     keystate_pressed,  ewc_prev_weapon);
	bind_action_msg(input_map, ek_R3,     keystate_pressed,  ewc_change_camera);
}
void init_swim_input_map(user_input_map* input_map)
{
	if (input_map)
		return;

	input_map = create_user_input_map();
	if (!input_map)
		return;

	bind_axis_msg(input_map,   ek_lanalogup,    esc_move_forward);
	bind_axis_msg(input_map,   ek_lanalogright, esc_move_right);
	bind_action_msg(input_map, ek_L3,           keystate_pressed, esc_swim_hard);

	bind_action_msg(input_map, ek_circle, keystate_pressed, esc_dive);
	bind_action_msg(input_map, ek_R3,     keystate_pressed, esc_change_camera);
}
void init_menu_input_map(user_input_map* input_map)
{
	if (input_map)
		return;

	input_map = create_user_input_map();
	if (!input_map)
		return;

	bind_action_msg(input_map, ek_dpadup,    keystate_repeated, emc_up);
	bind_action_msg(input_map, ek_dpaddown,  keystate_repeated, emc_down);
	bind_action_msg(input_map, ek_dpadright, keystate_repeated, emc_right);
	bind_action_msg(input_map, ek_dpadleft,  keystate_repeated, emc_left);

	bind_action_msg(input_map, ek_cross,  keystate_pressed,  emc_select);
	bind_action_msg(input_map, ek_circle, keystate_pressed,  emc_back);
}
void init_vehicle_input_map(user_input_map* input_map)
{
	if (input_map)
		return;

	input_map = create_user_input_map();
	if (!input_map)
		return;

	bind_axis_msg(input_map, ek_R2,           evc_accelrate);
	bind_axis_msg(input_map, ek_L2,           evc_reverse);
	bind_axis_msg(input_map, ek_square,       evc_break);
	bind_axis_msg(input_map, ek_lanalogright, evc_turn_right);

	bind_action_msg(input_map, ek_R1,    keystate_pressed, evc_aim_right);
	bind_action_msg(input_map, ek_L1,    keystate_pressed, evc_aim_left);
	bind_action_msg(input_map, ek_cross, keystate_pressed, evc_attack);

	bind_action_msg(input_map, ek_R3,     keystate_repeated, evc_horn);
	bind_action_msg(input_map, ek_select, keystate_pressed,  evc_change_camera);
}
void init_jet_input_map(user_input_map* input_map)
{
	if (input_map)
		return;

	input_map = create_user_input_map();
	if (!input_map)
		return;

	bind_axis_msg(input_map, ek_R2,           ejc_accelerate);
	bind_axis_msg(input_map, ek_L2,           ejc_decelerate);
	bind_axis_msg(input_map, ek_lanalogright, ejc_roll_right);
	bind_axis_msg(input_map, ek_lanalogup,    ejc_go_up);
	bind_axis_msg(input_map, ek_L1,           ejc_turn_left, -1.f);
	bind_axis_msg(input_map, ek_R1,           ejc_turn_right, 1.f);
	
	bind_action_msg(input_map, ek_L3,       keystate_pressed, ejc_toggle_wheels);
	bind_action_msg(input_map, ek_cross,    keystate_pressed, ejc_fire);
	bind_action_msg(input_map, ek_circle,   keystate_pressed, ejc_lunch_missle);
	bind_action_msg(input_map, ek_triangle, keystate_pressed, ejc_lunch_flares);
	bind_action_msg(input_map, ek_select,   keystate_pressed, egc_change_camera);
}

struct player_input_map
{
	user_input_map* walk = nullptr;
	user_input_map* jet = nullptr;
	user_input_map* swim = nullptr;
	user_input_map* vehicle = nullptr;
	user_input_map* menu = nullptr;
};
player_input_map players_input_maps[4];

bool player_one_init_input() 
{
	player_input_map* input_maps = &players_input_maps[0];
	
	init_menu_input_map(input_maps->menu);
	init_walk_input_map(input_maps->walk);
	init_swim_input_map(input_maps->swim);
	init_vehicle_input_map(input_maps->vehicle);
	init_jet_input_map(input_maps->jet);

	// no handlers yet for all the events cmds
}