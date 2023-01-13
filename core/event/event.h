#pragma once

#include <stdint.h>

enum einputdevice
{
	inputdevice_unknown = -1,

	inputdevice_kboard,
	inputdevice_mouse,
	inputdevice_gpad,

	inputdevice_count
};

struct event_key
{
	einputdevice devicetype = inputdevice_unknown;
	int32_t      key        = -1;
	int8_t       state      = -1;
	int8_t       mods       = -1;
	float        timestamp  = 0.0f;
};

struct key_detail
{
	float timestamp = 0.0f;
	int8_t state = -1;
};

extern bool event_init();
extern void event_add(event_key* in_event);
extern event_key* event_get();


