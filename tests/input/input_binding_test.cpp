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


void player1_move_forward(float invalue)
{
	printf("Player_1: Forward: %.2f\n", invalue);
}
void player1_move_sideward(float invalue)
{
	printf("Player_1: Sideward: %.2f\n", invalue);

}
void player1_dodge()
{
	printf("Player_1: Dodge\n");
	controller_vibrate_start(einputuser_0, 32000, 16000);
}
void player1_useitem()
{
	printf("Player_1: Useitem\n");
	controller_vibrate_end(einputuser_0);
}
void player1_attack()
{
	printf("Player_1: Attack\n");
}
void player1_shield()
{
	printf("Player_1: Shield\n");
}

bool player_one_init_input() 
{
	user_input_map* game = create_user_input_map();
	if (!game)
		return false;

	// actions bindings
	bind_action_msg(game, ek_circle, keystate_pressed, egc_dodge);
	bind_action_msg(game, ek_square, keystate_pressed, egc_useitem);
	bind_action_msg(game, ek_R1,     keystate_pressed, egc_attack);
	bind_action_msg(game, ek_L1,     keystate_pressed, egc_shield);

	// axes bindings
	bind_axis_msg(game, ek_lanalogup,    egc_forward,  -1.f);
	bind_axis_msg(game, ek_lanalogdown,  egc_forward,   1.f);
	bind_axis_msg(game, ek_lanalogleft,  egc_sideward, -1.f);
	bind_axis_msg(game, ek_lanalogright, egc_sideward,  1.f);

	// msg handlers
	bind_action_handler(game, egc_dodge,   player1_dodge);
	bind_action_handler(game, egc_useitem, player1_useitem);
	bind_action_handler(game, egc_attack,  player1_attack);
	bind_action_handler(game, egc_shield,  player1_shield);

	bind_axis_handler(game, egc_forward,  player1_move_forward);
	bind_axis_handler(game, egc_sideward, player1_move_sideward);

	if (!push_input_map(einputuser_0, game))
		return false;

	return true;
}








void player2_move_forward(float invalue)
{
	printf("Player_2: Forward %.2f\n", invalue);
}
void player2_move_sideward(float invalue)
{
	printf("Player_2: Sideward: %.2f\n", invalue);

}
void player2_dodge()
{
	printf("Player_2: Dodge\n");
	controller_vibrate_start(einputuser_1, 32000, 16000);
}
void player2_useitem()
{
	printf("Player_2: Useitem\n");
	controller_vibrate_end(einputuser_1);
}
void player2_attack()
{
	printf("Player_2: Attack\n");
}
void player2_shield()
{
	printf("Player_2: Shield\n");
}


bool player2_default_input_map()
{
	user_input_map* default_input_map = create_user_input_map();
	if (!default_input_map)
		return false;

	// actions bindings
	bind_action_msg(default_input_map, ek_circle, keystate_pressed, egc_dodge);
	bind_action_msg(default_input_map, ek_square, keystate_pressed, egc_useitem);
	bind_action_msg(default_input_map, ek_R1, keystate_pressed, egc_attack);
	bind_action_msg(default_input_map, ek_L1, keystate_pressed, egc_shield);

	// axes bindings
	bind_axis_msg(default_input_map, ek_lanalogup, egc_forward, -1.f);
	bind_axis_msg(default_input_map, ek_lanalogdown, egc_forward, 1.f);
	bind_axis_msg(default_input_map, ek_lanalogleft, egc_sideward, -1.f);
	bind_axis_msg(default_input_map, ek_lanalogright, egc_sideward, 1.f);

	// msg handlers
	bind_action_handler(default_input_map, egc_dodge, player2_dodge);
	bind_action_handler(default_input_map, egc_useitem, player2_useitem);
	bind_action_handler(default_input_map, egc_attack, player2_attack);
	bind_action_handler(default_input_map, egc_shield, player2_shield);

	bind_axis_handler(default_input_map, egc_forward, player2_move_forward);
	bind_axis_handler(default_input_map, egc_sideward, player2_move_sideward);
}
bool player2_input_map_type_B()
{
	user_input_map* input_map_type_B = create_user_input_map();
	if (!input_map_type_B)
		return false;

	// actions bindings
	bind_action_msg(input_map_type_B, ek_triangle, keystate_pressed, egc_dodge);
	bind_action_msg(input_map_type_B, ek_cross,    keystate_pressed, egc_useitem);
	bind_action_msg(input_map_type_B, ek_square,   keystate_pressed, egc_attack);
	bind_action_msg(input_map_type_B, ek_circle,   keystate_pressed, egc_shield);

	// axes bindings
	bind_axis_msg(input_map_type_B, ek_dpadup,    egc_forward, -1.f);
	bind_axis_msg(input_map_type_B, ek_dpaddown,  egc_forward, 1.f);
	bind_axis_msg(input_map_type_B, ek_dpadleft,  egc_sideward, -1.f);
	bind_axis_msg(input_map_type_B, ek_dpadright, egc_sideward, 1.f);

	// msg handlers
	bind_action_handler(input_map_type_B, egc_dodge,   player2_dodge);
	bind_action_handler(input_map_type_B, egc_useitem, player2_useitem);
	bind_action_handler(input_map_type_B, egc_attack,  player2_attack);
	bind_action_handler(input_map_type_B, egc_shield,  player2_shield);

	bind_axis_handler(input_map_type_B, egc_forward, player2_move_forward);
	bind_axis_handler(input_map_type_B, egc_sideward, player2_move_sideward);
}

bool player_two_init_input()
{
	user_input_map* game = create_user_input_map();
	if (!game)
		return false;

	// actions bindings
	bind_action_msg(game, ek_circle, keystate_pressed, egc_dodge);
	bind_action_msg(game, ek_square, keystate_pressed, egc_useitem);
	bind_action_msg(game, ek_R1, keystate_pressed, egc_attack);
	bind_action_msg(game, ek_L1, keystate_pressed, egc_shield);

	// axes bindings
	bind_axis_msg(game, ek_lanalogup, egc_forward, -1.f);
	bind_axis_msg(game, ek_lanalogdown, egc_forward, 1.f);
	bind_axis_msg(game, ek_lanalogleft, egc_sideward, -1.f);
	bind_axis_msg(game, ek_lanalogright, egc_sideward, 1.f);

	// msg handlers
	bind_action_handler(game, egc_dodge, player2_dodge);
	bind_action_handler(game, egc_useitem, player2_useitem);
	bind_action_handler(game, egc_attack, player2_attack);
	bind_action_handler(game, egc_shield, player2_shield);

	bind_axis_handler(game, egc_forward, player2_move_forward);
	bind_axis_handler(game, egc_sideward, player2_move_sideward);

	if (!push_input_map(einputuser_1, game))
		return false;

	return true;
}