#include "event.h"
#include "../../common.h"

struct key_detail
{
	float  timestamp = 0.0f;
	float  value     = 0.0f;
	int8_t state     = keystate_unknown;
	int8_t mods      = emodkey_unknown;
};

static Queue *user_eventqueue[4];
static Array *users_keydetail[4];
static float  mouse_x = 0.0f;
static float  mouse_y = 0.0f;

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

void key_setvalue(int8_t inuseridx, int16_t inkey, float invalue)
{
	key_detail* kd = keydetail_get(inuseridx, inkey);

	if (!kd)
		return;

	kd->value = invalue;
}
/***************************************
*         END: HELPER FUNCTION         *
****************************************/


/**************************************
*    BEGIN: INPUT DEBUGGING STUFF     *
***************************************/
static const char* keys_name[256];
static const char* keys_state_name[keystate_count];
static const char* modkeys_name[8];

const char* keyname(int16_t inkey) { if (inkey > 255 || inkey < 0) return "no_name";                               return keys_name[inkey]; }
const char* keystatename(int8_t inkeystate) { if (inkeystate > keystate_count || inkeystate < 0) return "no_name"; return keys_state_name[inkeystate]; }
const char* modkeyname(int8_t inmodkey) { if (inmodkey > 8 || inmodkey < 0) return "no_name";                      return modkeys_name[inmodkey]; }
void input_debugging_stuff_init()
{
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
}
/**************************************
*    BEGIN: INPUT DEBUGGING STUFF     *
***************************************/



/***************************************
*   BEGIN: USERINPUT.h HEADER IMPL     *
****************************************/
struct actionmsgdef
{
	uint16_t msg[keystate_count][emodkey_count];
};

struct axismsgdef
{
	uint16_t msg[emodkey_count];
};

struct msghandlerdef
{
	union handlerdef
	{
		void(*axis_handler)(float) = nullptr;
		void(*action_handler)();
	} handler;
};

Array *user_actionlayout[4];
Array *user_axislayout[4];
Array *user_inputhandlers[4];

void mouse_get_pos(float* outx, float* outy)
{
	if (outx)
		*outx = mouse_x;

	if (outy)
		*outy = mouse_y;
}

void inputlayout_init(uint8_t ininputuser, uint16_t inmsgcount)
{
	if (ininputuser > 3 || ininputuser < 0)
		return;

	Array *imd_actionlayout = user_actionlayout[ininputuser];
	Array *img_axislayout   = user_axislayout[ininputuser];
	Array *mhd              = user_inputhandlers[ininputuser];

	if (img_axislayout || imd_actionlayout || mhd)
		return;

	const char* array_name = nullptr;

	switch (ininputuser)
	{
	case 0: array_name = "array_actionmap_user_0"; break;
	case 1: array_name = "array_actionmap_user_1"; break;
	case 2: array_name = "array_actionmap_user_2"; break;
	case 3: array_name = "array_actionmap_user_3"; break;
	}
	user_actionlayout[ininputuser]  = array_create(array_name, ek_count, sizeof(actionmsgdef));

	switch (ininputuser)
	{
	case 0: array_name = "array_axismap_user_0"; break;
	case 1: array_name = "array_axismap_user_1"; break;
	case 2: array_name = "array_axismap_user_2"; break;
	case 3: array_name = "array_axismap_user_3"; break;
	}
	user_axislayout[ininputuser]    = array_create(array_name, ek_count, sizeof(axismsgdef));

	switch (ininputuser)
	{
	case 0: array_name = "array_msghandler_user_0"; break;
	case 1: array_name = "array_msghandler_user_1"; break;
	case 2: array_name = "array_msghandler_user_2"; break;
	case 3: array_name = "array_msghandler_user_3"; break;
	}
	user_inputhandlers[ininputuser] = array_create(array_name, inmsgcount, sizeof(msghandlerdef));
}

void bind_action_msg(uint8_t ininputuser, int16_t inkey, uint8_t inkeystate, uint16_t inmsgid, uint8_t inmods)
{
	Array* actions = user_actionlayout[ininputuser];
	if (!actions)
		return;

	actionmsgdef* msgdef = (actionmsgdef*)array_get(actions, inkey);
	if (!msgdef)
		return;

	msgdef->msg[inkeystate][inmods] = inmsgid;
}

void bind_axis_msg(uint8_t ininputuser, int16_t inkey, uint16_t inmsgid, float inaxisvalue, uint8_t inmods)
{
	Array* axes = user_axislayout[ininputuser];
	if (!axes)
		return;

	axismsgdef* msgdef = (axismsgdef*)array_get(axes, inkey);
	if (!msgdef)
		return;

	msgdef->msg[inmods] = inmsgid;
	key_setvalue(ininputuser, inkey, inaxisvalue);
}

void bind_action_handler(uint8_t ininputuser, uint16_t inmsgid, void(*action_handler)())
{
	Array* handlers = user_inputhandlers[ininputuser];
	if (!handlers)
		return;

	msghandlerdef* handlerdef = (msghandlerdef*)array_get(handlers, inmsgid);
	if (!handlerdef)
		return;

	handlerdef->handler.action_handler = action_handler;
}

void bind_axis_handler(uint8_t ininputuser, uint16_t inmsgid, void(*axis_handler)(float))
{
	Array* handlers = user_inputhandlers[ininputuser];
	if (!handlers)
		return;

	msghandlerdef* handlerdef = (msghandlerdef*)array_get(handlers, inmsgid);
	if (!handlerdef)
		return;

	handlerdef->handler.axis_handler = axis_handler;
}

void process_axes()
{
	int8_t         useridx = 0;
	Array* user_axes = nullptr;
	Array* user_keydetail = nullptr;
	Array* user_handlers = nullptr;
	axismsgdef* axismsg = nullptr;
	key_detail* kd = nullptr;
	msghandlerdef* msghandler = nullptr;

	while (useridx < 4)
	{
		user_axes = user_axislayout[useridx];
		user_keydetail = users_keydetail[useridx];
		user_handlers = user_inputhandlers[useridx];
		++useridx;

		if (!user_axes || !user_keydetail || !user_handlers)
			continue;

		for (int32_t key = 0; key < ek_count; ++key)
		{
			axismsg = (axismsgdef*)array_get(user_axes, key);

			if (!axismsg)
				continue;

			kd = (key_detail*)array_get(user_keydetail, key);

			if (!kd)
				continue;

			if (kd->state <= keystate_released)
				continue;

			msghandler = (msghandlerdef*)array_get(user_handlers, axismsg->msg[kd->mods]);
			if (msghandler && msghandler->handler.axis_handler)
			{
				msghandler->handler.axis_handler(kd->value);
			}
		}
	}
}

/***************************************
*     END: USERINPUT.h HEADER IMPL     *
****************************************/



/**************************************
*    BEGIN: EVENT HANDLERS            *
***************************************/
typedef void(*event_handler)(uint8_t useridx, eventdef* inev);
event_handler event_handlers[eventtype_count];

void kboard_event_handler(uint8_t useridx, eventdef* inev)
{
	if (!inev)
		return;

	event_kboard* ev = &inev->kboard;

	//printf("key: %s | %s | %s \n", keyname(ev->key), keystatename(ev->state), modkeyname(ev->mods));

	Array         *user_actions  = user_actionlayout[useridx];
	Array         *user_handlers = user_inputhandlers[useridx];
	actionmsgdef  *actionmsg     = nullptr;
	msghandlerdef *msghandler    = nullptr;
	uint16_t       msg           = 0;

	if (user_actions && user_handlers)
	{
		actionmsg = (actionmsgdef*)array_get(user_actions, ev->key);
		if (actionmsg)
		{
			msg = actionmsg->msg[ev->state][ev->mods];

			msghandler = (msghandlerdef*)array_get(user_handlers, msg);
			if (msghandler && msghandler->handler.action_handler)
			{
				msghandler->handler.action_handler();
			}
		}
	}
}

void mouse_event_handler(uint8_t useridx, eventdef* inev)
{
	if (!inev)
		return;

	event_mouse* ms = &inev->mouse;

	printf("button: %s | %s | %s \n", keyname(ms->button), keystatename(ms->state), modkeyname(ms->mods));

	// loop through user_0 action map and invoke if nay

	// or

	// collect actions from user_0 
}

void gpad_event_handler(uint8_t useridx, eventdef* inev)
{
	// get action from user through inev->gpad.useridx;

	// or

	// collect actions from user through inev->gpad.useridx;
}
/**************************************
*    END: EVENT HANDLERS              *
***************************************/




/***************************************
*     BEGIN: EVENT.h HEADER IMPL       *
****************************************/
bool event_init()
{
	user_eventqueue[0] = queue_create("array_eventqueue_user0", 64, sizeof(eventdef));
	user_eventqueue[1] = queue_create("array_eventqueue_user1", 64, sizeof(eventdef));
	user_eventqueue[2] = queue_create("array_eventqueue_user2", 64, sizeof(eventdef));
	user_eventqueue[3] = queue_create("array_eventqueue_user3", 64, sizeof(eventdef));
	
	users_keydetail[0] = array_create("array_keydetail_user0", 256, sizeof(key_detail));
	users_keydetail[1] = array_create("array_keydetail_user1", 256, sizeof(key_detail));
	users_keydetail[2] = array_create("array_keydetail_user2", 256, sizeof(key_detail));
	users_keydetail[3] = array_create("array_keydetail_user3", 256, sizeof(key_detail));
	
	for (int32_t useridx = 0; useridx < 4; ++useridx)
	{
		if (!users_keydetail[useridx] || !user_eventqueue[useridx])
		{
			return false;
		}
	}

	event_handlers[eventtype_kboard] = kboard_event_handler;
	event_handlers[eventtype_mouse]  = mouse_event_handler;
	event_handlers[eventtype_gpad]   = gpad_event_handler;

	input_debugging_stuff_init();

	return true;
}

void onevent_kboard(int8_t inuserid, int16_t inkey, int8_t instate, int8_t inmods, float intimestamp)
{
	if (inuserid < 0 || inuserid > 3)
		return;

	Queue   *ev_queue = user_eventqueue[inuserid];
	key_detail *kd    = keydetail_get(inuserid, inkey);

	if (!kd)
		return;

	kd->state     = instate;
	kd->mods      = inmods;
	kd->timestamp = intimestamp;

	if (!ev_queue)
		return;

	eventdef ev;
	ev.type         = eventtype_kboard;
	ev.timestamp    = intimestamp;
	ev.kboard.key   = inkey;
	ev.kboard.state = instate;
	ev.kboard.mods  = inmods;

	queue_add(ev_queue, &ev);
}

void onevent_mouse_button(int8_t inuserid, int16_t inbutton, int8_t instate, int8_t inmods, float intimestamp)
{
	if (inuserid < 0 || inuserid > 3)
		return;

	Queue      *ev_queue = user_eventqueue[inuserid];
	key_detail *kd       = keydetail_get(inuserid, inbutton);

	if (!kd)
		return;

	kd->state     = instate;
	kd->mods      = inmods;
	kd->timestamp = intimestamp;

	if (!ev_queue)
		return;

	eventdef ev;
	ev.type         = eventtype_mouse;
	ev.timestamp    = intimestamp;
	ev.mouse.button = inbutton;
	ev.mouse.state  = instate;
	ev.mouse.mods   = inmods;

	queue_add(ev_queue, &ev);
}

void onevent_gpad_button(int8_t inuserid, int16_t inbutton, int8_t state, float intimestamp)
{

}

void onevent_gpad_axis(int8_t inuserid, int16_t inaxis, float invalue)
{

}

void onevent_mouse_move(float inx, float iny)
{
	mouse_x = inx;
	mouse_y = iny;
}

void event_process()
{
	process_axes();

	eventdef      *ev         = nullptr;
	event_handler  ev_handler = nullptr;
	Queue         *ev_queue   = nullptr;
	
	for (uint8_t queueidx = 0; queueidx < 4; ++queueidx)
	{
		ev_queue = user_eventqueue[queueidx];
	
		if (!ev_queue)
			return;
		
		while (queue_size(ev_queue))
		{
			ev = (eventdef*)queue_get(ev_queue);
	
			if (!ev)
				return;
	
			if (ev->type == eventtype_unknown || ev->type > eventtype_count - 1)
				return;
	
			ev_handler = event_handlers[ev->type];
			if (ev_handler)
			{
				ev_handler(queueidx, ev);
			}
		}
	
		queue_clear(ev_queue);
	}
}
/***************************************
*       END: EVENT.h HEADER IMPL       *
****************************************/








