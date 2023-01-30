#include "input_binding_test.h"

#include "../../common.h"

enum ewalkcmd
{
	// movement cmds
	ewc_move_forward = 1,
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
	ejc_accelerate = 1,
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
	esc_move_forward = 1,
	esc_move_right,
	esc_swim_hard,
	esc_dive,

	esc_change_camera,

	esc_count,
};

enum evehiclecmd
{
	// movement cmds
	evc_accelrate = 1,
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
	emc_up = 1,
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



void init_walk_input_map   (const char* input_map_name, user_input_map** input_map)
{
	if (!input_map)
		return;

	*input_map = create_user_input_map(input_map_name);
	if (!(*input_map))
		return;

	user_input_map* input = *input_map;

	bind_axis_msg  (input, ek_lanalogup,    ewc_move_forward);
	bind_axis_msg  (input, ek_lanalogright, ewc_move_right);
	bind_action_msg(input, ek_L3,           keystate_pressed,  ewc_run);
	bind_action_msg(input, ek_cross,        keystate_pressed,  ewc_jump);
	bind_action_msg(input, ek_circle,       keystate_pressed,  ewc_crouch);
	bind_action_msg(input, ek_circle,       keystate_repeated, ewc_lay);
	bind_action_msg(input, ek_square,       keystate_pressed,  ewc_attack);
	bind_action_msg(input, ek_R1,           keystate_pressed,  ewc_next_weapon);
	bind_action_msg(input, ek_L1,           keystate_pressed,  ewc_prev_weapon);
	bind_action_msg(input, ek_R3,           keystate_pressed,  ewc_change_camera);

	bind_axis_handler  (input, ewc_move_forward,  [](float v) {printf("character_forward: %.2f\n", v); });
	bind_axis_handler  (input, ewc_move_right,    [](float v) {printf("right: %.2f\n", v); });
	bind_action_handler(input, ewc_jump,          []() {printf("character_jump\n"); });
	bind_action_handler(input, ewc_crouch,        []() {printf("character_crouch\n"); });
	bind_action_handler(input, ewc_lay,           []() {printf("character_lay\n"); });
	bind_action_handler(input, ewc_attack,        []() {printf("character_attack\n"); });
	bind_action_handler(input, ewc_next_weapon,   []() {printf("character_next_weapon\n"); });
	bind_action_handler(input, ewc_prev_weapon,   []() {printf("character_prev_weapon\n"); });
	bind_action_handler(input, ewc_change_camera, []() {printf("character_change_camera\n"); });
}
void init_swim_input_map   (const char* input_map_name, user_input_map** input_map)
{
	if (!input_map)
		return;

	*input_map = create_user_input_map(input_map_name);
	if (!(*input_map))
		return;

	user_input_map* input = *input_map;

	bind_axis_msg  (input, ek_lanalogup,    esc_move_forward);
	bind_axis_msg  (input, ek_lanalogright, esc_move_right);
	bind_action_msg(input, ek_L3,           keystate_pressed, esc_swim_hard);
	bind_action_msg(input, ek_circle,       keystate_pressed, esc_dive);
	bind_action_msg(input, ek_R3,           keystate_pressed, esc_change_camera);

	bind_axis_handler  (input, esc_move_forward,  [](float v) {printf("swim_forward: %.2f\n", v); });
	bind_axis_handler  (input, esc_move_right,    [](float v) {printf("swim_right: %.2f\n", v); });
	bind_action_handler(input, esc_swim_hard,     []() {printf("swim_hard\n"); });
	bind_action_handler(input, esc_dive,          []() {printf("swim_dive\n"); });
	bind_action_handler(input, esc_change_camera, []() {printf("swim_change_camera\n"); });
}
void init_menu_input_map   (const char* input_map_name, user_input_map** input_map)
{
	if (!input_map)
		return;

	*input_map = create_user_input_map(input_map_name);
	if (!(*input_map))
		return;

	user_input_map* input = *input_map;

	bind_action_msg(input, ek_dpadup,    keystate_repeated, emc_up);
	bind_action_msg(input, ek_dpaddown,  keystate_repeated, emc_down);
	bind_action_msg(input, ek_dpadright, keystate_repeated, emc_right);
	bind_action_msg(input, ek_dpadleft,  keystate_repeated, emc_left);
	bind_action_msg(input, ek_cross,  keystate_pressed,  emc_select);
	bind_action_msg(input, ek_circle, keystate_pressed,  emc_back);

	bind_action_handler(input, emc_up    , []() {printf("menu_up\n"); });
	bind_action_handler(input, emc_down  , []() {printf("menu_down\n"); });
	bind_action_handler(input, emc_right , []() {printf("menu_right\n"); });
	bind_action_handler(input, emc_left  , []() {printf("menu_left\n"); });
	bind_action_handler(input, emc_select, []() {printf("menu_select\n"); });
	bind_action_handler(input, emc_back  , []() {printf("menu_back\n"); });
}
void init_vehicle_input_map(const char* input_map_name, user_input_map** input_map)
{
	if (!input_map)
		return;

	*input_map = create_user_input_map(input_map_name);
	if (!(*input_map))
		return;

	user_input_map* input = *input_map;

	bind_axis_msg  (input, ek_R2,           evc_accelrate);
	bind_axis_msg  (input, ek_L2,           evc_reverse);
	bind_axis_msg  (input, ek_square,       evc_break);
	bind_axis_msg  (input, ek_lanalogright, evc_turn_right);
	bind_action_msg(input, ek_R1,           keystate_pressed,  evc_aim_right);
	bind_action_msg(input, ek_L1,           keystate_pressed,  evc_aim_left);
	bind_action_msg(input, ek_cross,        keystate_pressed,  evc_attack);
	bind_action_msg(input, ek_R3,           keystate_repeated, evc_horn);
	bind_action_msg(input, ek_select,       keystate_pressed,  evc_change_camera);

	bind_axis_handler  (input, evc_accelrate    , [](float v){printf("vehicle_accelerate: %.2f\n", v);});
	bind_axis_handler  (input, evc_reverse      , [](float v){printf("vehicle_reverse: %.2f\n", v);});
	bind_axis_handler  (input, evc_break        , [](float v){printf("vehicle_break: %.2f\n", v);});
	bind_axis_handler  (input, evc_turn_right   , [](float v){printf("vehicle_turn_right: %.2f\n", v);});
	bind_action_handler(input, evc_aim_right    , [](){printf("vehicle_airm_right\n");});
	bind_action_handler(input, evc_aim_left     , [](){printf("vehicle_airm_left\n");});
	bind_action_handler(input, evc_attack       , [](){printf("vehicle_attack\n");});
	bind_action_handler(input, evc_horn         , [](){printf("vehicle_horn\n");});
	bind_action_handler(input, evc_change_camera, [](){printf("vehicle_change_camera\n");});
}
void init_jet_input_map    (const char* input_map_name, user_input_map** input_map)
{
	if (!input_map)
		return;

	*input_map = create_user_input_map(input_map_name);
	if (!(*input_map))
		return;

	user_input_map* input = *input_map;

	bind_axis_msg  (input, ek_R2,           ejc_accelerate);
	bind_axis_msg  (input, ek_L2,           ejc_decelerate);
	bind_axis_msg  (input, ek_lanalogright, ejc_roll_right);
	bind_axis_msg  (input, ek_lanalogup,    ejc_go_up);
	bind_axis_msg  (input, ek_L1,           ejc_turn_left, -1.f);
	bind_axis_msg  (input, ek_R1,           ejc_turn_right, 1.f);
	bind_action_msg(input, ek_L3,           keystate_pressed, ejc_toggle_wheels);
	bind_action_msg(input, ek_cross,        keystate_pressed, ejc_fire);
	bind_action_msg(input, ek_circle,       keystate_pressed, ejc_lunch_missle);
	bind_action_msg(input, ek_triangle,     keystate_pressed, ejc_lunch_flares);
	bind_action_msg(input, ek_select,       keystate_pressed, egc_change_camera);

	bind_axis_handler  (input, ejc_accelerate,    [](float v){printf("jet_accelerate: %.2f\n", v);});
	bind_axis_handler  (input, ejc_decelerate,    [](float v){printf("jet_decelerate: %.2f\n", v);});
	bind_axis_handler  (input, ejc_roll_right,    [](float v){printf("jet_roll_right: %.2f\n", v);});
	bind_axis_handler  (input, ejc_go_up,         [](float v){printf("jet_go_up: %.2f\n", v);});
	bind_axis_handler  (input, ejc_turn_left,     [](float v){printf("jet_turn_left: %.2f\n", v);});
	bind_axis_handler  (input, ejc_turn_right,    [](float v){printf("jet_turn_right: %.2f\n", v);});
	bind_action_handler(input, ejc_toggle_wheels, [](){printf("jet_toggle_wheel\n");});
	bind_action_handler(input, ejc_fire,          [](){printf("jet_fire\n");});
	bind_action_handler(input, ejc_lunch_missle,  [](){printf("jet_lunch_missle\n");});
	bind_action_handler(input, ejc_lunch_flares,  [](){printf("jet_lunch_flares\n");});
	bind_action_handler(input, egc_change_camera, [](){printf("jet_change_camera\n");});
}

struct player_input_map
{
	user_input_map *walk    = nullptr;
	user_input_map *jet     = nullptr;
	user_input_map *swim    = nullptr;
	user_input_map *vehicle = nullptr;
	user_input_map *menu    = nullptr;
};
player_input_map players_input_maps[4];

bool player_one_init_input() 
{
	player_input_map* input_maps = &players_input_maps[0];
	
	init_menu_input_map   ("player_1: menu_input_map",    &input_maps->menu);
	init_walk_input_map   ("player_1: walk_input_map",    &input_maps->walk);
	init_swim_input_map   ("player_1: swim_input_map",    &input_maps->swim);
	init_vehicle_input_map("player_1: vehicle_input_map", &input_maps->vehicle);
	init_jet_input_map    ("player_1: jet_input_map",     &input_maps->jet);

	// no handlers yet for all the events cmds

	push_input_map(einputuser_0, input_maps->walk);
	return true;
}

bool player_two_init_input()
{
	return true;
}