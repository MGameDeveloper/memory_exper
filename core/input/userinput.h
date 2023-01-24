#pragma once

#include <stdint.h>
#include "keys.h"


enum einputuser
{
	einputuser_0,
	einputuser_1,
	einputuser_2,
	einputuser_3,

	einputuser_count,
};

// defined in event.cpp
struct user_input_map;
extern user_input_map* create_user_input_map();
extern void push_input_map(uint8_t ininputuser, user_input_map* input_map);
extern void pop_input_map(uint8_t ininputuser);

extern void bind_action_msg(user_input_map* input_map, int16_t inkey, uint8_t inkeystate, uint16_t inmsgid, uint8_t inmods = emodkey_unknown);
extern void bind_axis_msg(user_input_map* input_map, int16_t inkey, uint16_t inmsgid, float inaxisvalue = 0.f, uint8_t inmods = emodkey_unknown);
extern void bind_action_handler(user_input_map* input_map, uint16_t inmsgid, void(*action_handler)());
extern void bind_axis_handler(user_input_map* input_map, uint16_t inmsgid, void(*axis_handler)(float));

extern void mouse_get_pos(float* outx, float* outy);


// define in xinput_interface.h
extern void controller_vibrate_start(uint8_t ininputuser, uint16_t inleftmotorspeed, uint16_t inrightmotorspeed);
extern void controller_vibrate_end(uint8_t ininputuser);