#pragma once

#include <stdint.h>

enum eventtype
{
	eventtype_unknown = -1,

	eventtype_kboard,
	eventtype_mouse,
	eventtype_gpad,

	eventtype_count
};

struct event_kboard
{
	int16_t key   = -1;
	int8_t  state = -1;
	int8_t  mods  = -1;
};

struct event_mouse
{
	int16_t button = -1;
	int8_t  state  = -1;
	int8_t  mods   = -1;
};

struct event_gpad
{
	int16_t button = -1;
	int8_t  state  = -1;
	int8_t  userid = 0;
	float   value  = 0.0f;
};

struct eventdef
{
	eventtype type      = eventtype_unknown;
	float     timestamp = 0.0f;

	union
	{
		event_kboard kboard;
		event_mouse  mouse;
		event_gpad   gpad;
	};

	eventdef() {} // the stupid compiler complains about the constructor is deleted
};

extern bool event_init();
extern void event_process();

extern void onevent_kboard(int8_t inuserid, int16_t inkey, int8_t instate, int8_t inmods);
extern void onevent_mouse_button(int8_t inuserid, int16_t inbutton, int8_t instate, int8_t inmods);
extern void onevent_gpad_button(int8_t inuserid, int16_t inbutton, int8_t state);
extern void onevent_gpad_axis(int8_t inuserid, int16_t inaxis, float invalue);
extern void onevent_mouse_move(float inx, float iny);
