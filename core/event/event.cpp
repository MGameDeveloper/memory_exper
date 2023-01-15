#include "event.h"
#include "../../common.h"

struct key_detail
{
	float  timestamp = 0.0f;
	float  value     = 0.0f;
	int8_t state     = keystate_unknown;
	int8_t mods      = emodkey_unknown;
};
static Queue* event_queue = nullptr;
static Array* users_keydetail[4];

// for debugging input
static const char* keys_name[256];
static const char* keys_state_name[keystate_count];
static const char* modkeys_name[8];
const char* keyname(int16_t inkey)          { if (inkey > 255 || inkey < 0) return "no_name";                       return keys_name[inkey]; }
const char* keystatename(int8_t inkeystate) { if (inkeystate > keystate_count || inkeystate < 0)  return "no_name"; return keys_state_name[inkeystate]; }
const char* modkeyname(int8_t inmodkey)     { if (inmodkey > 8 || inmodkey < 0) return "no_name";                   return modkeys_name[inmodkey]; }


extern bool event_init()
{
	event_queue = queue_create("queue_eventqueue", 64, sizeof(eventdef));
	if (!event_queue)
		return false;

	users_keydetail[0] = array_create("array_keydetail_user0", 256, sizeof(key_detail));
	users_keydetail[1] = array_create("array_keydetail_user1", 256, sizeof(key_detail));
	users_keydetail[2] = array_create("array_keydetail_user2", 256, sizeof(key_detail));
	users_keydetail[3] = array_create("array_keydetail_user3", 256, sizeof(key_detail));
	
	for (int32_t useridx = 0; useridx < 4; ++useridx)
	{
		if (!users_keydetail[useridx])
		{
			return false;
		}
	}

// for debugging input
#define KEY_NAME(KEY) keys_name[KEY] = #KEY
	KEY_NAME(ek_lmouse);
	KEY_NAME(ek_rmouse);
	KEY_NAME(ek_mmouse);
	KEY_NAME(ek_mouse_scrolldown);
	KEY_NAME(ek_mouse_scrollup);
	KEY_NAME(ek_a);
	KEY_NAME(ek_b);
	KEY_NAME(ek_c);
	KEY_NAME(ek_d);
	KEY_NAME(ek_e);
	KEY_NAME(ek_f);
	KEY_NAME(ek_g);
	KEY_NAME(ek_h);
	KEY_NAME(ek_i);
	KEY_NAME(ek_j);
	KEY_NAME(ek_k);
	KEY_NAME(ek_l);
	KEY_NAME(ek_m);
	KEY_NAME(ek_n);
	KEY_NAME(ek_o);
	KEY_NAME(ek_p);
	KEY_NAME(ek_q);
	KEY_NAME(ek_r);
	KEY_NAME(ek_s);
	KEY_NAME(ek_t);
	KEY_NAME(ek_u);
	KEY_NAME(ek_v);
	KEY_NAME(ek_w);
	KEY_NAME(ek_x);
	KEY_NAME(ek_y);
	KEY_NAME(ek_z);
	KEY_NAME(ek_0);
	KEY_NAME(ek_1);
	KEY_NAME(ek_2);
	KEY_NAME(ek_3);
	KEY_NAME(ek_4);
	KEY_NAME(ek_5);
	KEY_NAME(ek_6);
	KEY_NAME(ek_7);
	KEY_NAME(ek_8);
	KEY_NAME(ek_9);
	KEY_NAME(ek_numpad0);
	KEY_NAME(ek_numpad1);
	KEY_NAME(ek_numpad2);
	KEY_NAME(ek_numpad3);
	KEY_NAME(ek_numpad4);
	KEY_NAME(ek_numpad5);
	KEY_NAME(ek_numpad6);
	KEY_NAME(ek_numpad7);
	KEY_NAME(ek_numpad8);
	KEY_NAME(ek_numpad9);
	KEY_NAME(ek_f1);
	KEY_NAME(ek_f2);
	KEY_NAME(ek_f3);
	KEY_NAME(ek_f4);
	KEY_NAME(ek_f5);
	KEY_NAME(ek_f6);
	KEY_NAME(ek_f7);
	KEY_NAME(ek_f8);
	KEY_NAME(ek_f9);
	KEY_NAME(ek_f10);
	KEY_NAME(ek_f11);
	KEY_NAME(ek_f12);
	KEY_NAME(ek_up);
	KEY_NAME(ek_down);
	KEY_NAME(ek_left);
	KEY_NAME(ek_right);
	KEY_NAME(ek_enter);
	KEY_NAME(ek_esc);
	KEY_NAME(ek_space);
	KEY_NAME(ek_backspace);
	KEY_NAME(ek_delete);
	KEY_NAME(ek_insert);
	KEY_NAME(ek_tab);
	KEY_NAME(ek_capslock);
	KEY_NAME(ek_numlock);
	KEY_NAME(ek_pageup);
	KEY_NAME(ek_pagedown);
	KEY_NAME(ek_end);
	KEY_NAME(ek_home);
	KEY_NAME(ek_decimal);
	KEY_NAME(ek_semicolon);
	KEY_NAME(ek_slash);
	KEY_NAME(ek_tilde);
	KEY_NAME(ek_left_bracket);
	KEY_NAME(ek_backslash);
	KEY_NAME(ek_right_bracket);
	KEY_NAME(ek_quote);
	KEY_NAME(ek_hyphen);
	KEY_NAME(ek_period);
	KEY_NAME(ek_equals);
	KEY_NAME(ek_comma);
	KEY_NAME(ek_multiply);
	KEY_NAME(ek_subtract);
	KEY_NAME(ek_add);
	KEY_NAME(ek_divide);
	KEY_NAME(ek_equals);
#undef KEY_NAME

#define KEY_STATE_NAME(KEY_STATE) keys_state_name[KEY_STATE] = #KEY_STATE
	KEY_STATE_NAME(keystate_unknown);
	KEY_STATE_NAME(keystate_pressed);
	KEY_STATE_NAME(keystate_released);
	KEY_STATE_NAME(keystate_repeated);
	KEY_STATE_NAME(keystate_doubleclick);
#undef KEY_STATE_NAME

#define MOD_KEY_NAME(MOD_KEY) modkeys_name[MOD_KEY] = #MOD_KEY
	MOD_KEY_NAME(emodkey_unknown);
	MOD_KEY_NAME(emodkey_ctrl);
	MOD_KEY_NAME(emodkey_shift);
	MOD_KEY_NAME(emodkey_shift | emodkey_ctrl);
	MOD_KEY_NAME(emodkey_alt);
	MOD_KEY_NAME(emodkey_alt | emodkey_ctrl);
	MOD_KEY_NAME(emodkey_alt | emodkey_shift);
	MOD_KEY_NAME(emodkey_alt | emodkey_shift | emodkey_ctrl);
#undef MOD_KEY_NAME

	return true;
}


/***************************************
*         BEGIN: HELPER FUNCTION       *
****************************************/
key_detail* keydetail_get(int8_t inuseridx, int16_t inkey)
{
	if (inuseridx > 3 || inuseridx < 0)
		return nullptr;

	Array* user_kd = users_keydetail[inuseridx];

	if (!user_kd)
		return nullptr;

	return (key_detail*)array_get(user_kd, inkey);
}
/***************************************
*         END: HELPER FUNCTION         *
****************************************/


void keyvalue_set(int8_t inuseridx, int16_t inkey, float invalue)
{
	key_detail* kd = keydetail_get(inuseridx, inkey);

	if (!kd)
		return;

	kd->value = invalue;
}

void onevent_kboard(int16_t inkey, int8_t instate, int8_t inmods, float intimestamp)
{
	// keyboard and mouse only available for user 0
	key_detail* kd = keydetail_get(0, inkey);
	if (!kd)
		return;

	kd->mods      = inmods;
	kd->state     = instate;
	kd->timestamp = intimestamp;

	if (!event_queue)
		return;

	eventdef ev;
	ev.type         = eventtype_kboard;
	ev.timestamp    = intimestamp;
	ev.kboard.key   = inkey;
	ev.kboard.state = instate;
	ev.kboard.mods  = inmods;

	queue_add(event_queue, &ev);
}

void onevent_mouse_button(int16_t inbutton, int8_t instate, int8_t inmods, float intimestamp)
{
	key_detail* kd = keydetail_get(0, inbutton);
	if (!kd)
		return;

	kd->state     = instate;
	kd->mods      = inmods;
	kd->timestamp = intimestamp;

	if (!event_queue)
		return;

	eventdef ev;
	ev.type         = eventtype_mouse;
	ev.timestamp    = intimestamp;
	ev.mouse.button = inbutton;
	ev.mouse.state  = instate;
	ev.mouse.mods   = inmods;

	queue_add(event_queue, &ev);
}

void onevent_gpad_button(int8_t inuserid, int16_t inbutton, int8_t state, float intimestamp)
{

}

void onevent_gpad_axis(int8_t inuserid, int16_t inaxis, float invalue)
{

}

void event_process()
{
	if (!event_queue)
		return;

	eventdef* ev = nullptr;
	while (queue_size(event_queue))
	{
		ev = (eventdef*)queue_get(event_queue);

		if (!ev)
			break;

		switch (ev->type)
		{
		case eventtype_kboard:
		{
			event_kboard kb = ev->kboard;
			printf("key: %s | %s | %s \n", keyname(kb.key), keystatename(kb.state), modkeyname(kb.mods));
		}
			break;

		case eventtype_mouse:
		{
			event_mouse ms = ev->mouse;
			printf("button: %s | %s | %s \n", keyname(ms.button), keystatename(ms.state), modkeyname(ms.mods));
		}
			break;

		case eventtype_gpad:
		{

		}
			break;
		}
	}

	queue_clear(event_queue);
}