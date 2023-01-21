#pragma once

#include <stdint.h>
#include "keys.h"

// defined int event.cpp
extern void mouse_get_pos(float* outx, float* outy);

enum einputuser
{
	einputuser_0,
	einputuser_1,
	einputuser_2,
	einputuser_3,

	einputuser_count,
};

extern void inputlayout_init(uint8_t ininputuser, uint16_t inmsgcount);
extern void bind_action_msg(uint8_t ininputuser, int16_t inkey, uint8_t inkeystate, uint16_t inmsgid, uint8_t inmodes = emodkey_unknown);
extern void bind_axis_msg(uint8_t ininputuser, int16_t inkey, uint16_t inmsgid, float inaxisvalue, uint8_t inmods = emodkey_unknown);
extern void bind_action_handler(uint8_t ininputuser, uint16_t inmsgid, void(*action_handler)());
extern void bind_axis_handler(uint8_t ininputuser, uint16_t inmsgid,   void(*axis_handler)(float));

// define in xinput_interface.h
extern void controller_vibrate_start(uint8_t ininputuser, uint16_t inleftmotorspeed, uint16_t inrightmotorspeed);
extern void controller_vibrate_end(uint8_t ininputuser);