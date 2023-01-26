#include "event.h"
#include "../../common.h"

#define EVENT_COUNT 64

struct eventdef_queue
{
	uint16_t get_idx = 0;
	uint16_t add_idx = 0;
	eventdef events[EVENT_COUNT];
};
bool      is_event_queue_empty(eventdef_queue* queue)
{
	if (!queue)
		return false;

	return (queue->get_idx == queue->add_idx);
}
void      add_event_to_queue(eventdef_queue* queue, eventdef* event)
{
	if (!queue || !event)
		return;

	if (queue->add_idx >= EVENT_COUNT)
		return;

	uint32_t idx = queue->add_idx++;
	memcpy(&queue->events[idx], event, sizeof(eventdef));
}
eventdef* get_event_from_queue(eventdef_queue* queue)
{
	if (!queue)
		return nullptr;

	if (is_event_queue_empty(queue))
		return nullptr;

	uint16_t idx = queue->get_idx++;

	return &queue->events[idx];
}
void      clear_event_queue(eventdef_queue* queue)
{
	if (!queue)
		return;

	queue->add_idx = 0;
	queue->get_idx = 0;
	memset(queue->events, 0, sizeof(eventdef) * EVENT_COUNT);
}

//struct key_detail
//{
//	float  timestamp = 0.0f;
//	float  value     = 0.0f;
//	int8_t state     = keystate_unknown;
//	int8_t mods      = emodkey_unknown;
//};
//
//static Queue *user_eventqueue[4];
//static Array *users_keydetail[4];
static float  mouse_x = 0.0f;
static float  mouse_y = 0.0f;

/***************************************
*         BEGIN: HELPER FUNCTION       *
****************************************/
//key_detail* keydetail_get(int8_t inuseridx, int16_t inkey)
//{
//	if (inuseridx > 3 || inuseridx < 0)
//		return nullptr;
//
//	Array* user_kd = users_keydetail[inuseridx];
//
//	if (!user_kd)
//		return nullptr;
//
//	return (key_detail*)array_get(user_kd, inkey);
//}
//
//void key_setvalue(int8_t inuseridx, int16_t inkey, float invalue)
//{
//	key_detail* kd = keydetail_get(inuseridx, inkey);
//
//	if (!kd)
//		return;
//
//	kd->value = invalue;
//}
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
	KEY_NAME(ek_cross);
	KEY_NAME(ek_circle);
	KEY_NAME(ek_triangle);
	KEY_NAME(ek_square);
	KEY_NAME(ek_dpadup);
	KEY_NAME(ek_dpaddown);
	KEY_NAME(ek_dpadleft);
	KEY_NAME(ek_dpadright);
	KEY_NAME(ek_L1);
	KEY_NAME(ek_L2);
	KEY_NAME(ek_L3);
	KEY_NAME(ek_R1);
	KEY_NAME(ek_R2);
	KEY_NAME(ek_R3);
	KEY_NAME(ek_start);
	KEY_NAME(ek_select);
	KEY_NAME(ek_lanalogup);
	KEY_NAME(ek_lanalogdown);
	KEY_NAME(ek_lanalogright);
	KEY_NAME(ek_lanalogleft);
	KEY_NAME(ek_ranalogup);
	KEY_NAME(ek_ranalogdown);
	KEY_NAME(ek_ranalogright);
	KEY_NAME(ek_ranalogleft);
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
//struct actionmsgdef
//{
//	uint16_t msg[keystate_count][emodkey_count];
//};
//
//struct axismsgdef
//{
//	uint16_t msg[emodkey_count];
//};
//
//struct msghandlerdef
//{
//	union handlerdef
//	{
//		void(*axis_handler)(float) = nullptr;
//		void(*action_handler)();
//	} handler;
//};
//
//Array *user_actionlayout[4];
//Array *user_axislayout[4];
//Array *user_inputhandlers[4];


#define USER_COUNT 4
#define KEY_COUNT ek_count 
#define CMD_COUNT ek_count
#define INPUT_MAP_COUNT 3


/***************************************
*   BEGIN: USER INPUT MAP STACK IMPL   *
****************************************/
union key_handler_def
{
	void (*axis)(float) = nullptr;
	void (*action)();
};

struct key_action_def
{
	uint16_t cmd[keystate_count][emodkey_count];
};

struct key_axis_def
{
	uint16_t cmd;
	float    value;
};

struct user_input_map
{
	key_action_def  actions[KEY_COUNT];
	key_axis_def    axes[KEY_COUNT];
	key_handler_def handlers[CMD_COUNT];
};

struct user_input_map_stack
{
	user_input_map input_maps[INPUT_MAP_COUNT];
	int8_t idx = 0;
};

void add_input_map_to_stack(user_input_map_stack* stack, user_input_map* input_map)
{
	if (!stack || !input_map)
		return;

	if (stack->idx >= INPUT_MAP_COUNT)
		return; // mean it's full

	if (stack->idx == -1)
		stack->idx = 0;

	int32_t idx = stack->idx++;
	memcpy(&stack->input_maps[idx], input_map, sizeof(user_input_map));
}
void remove_top_input_map_from_stack(user_input_map_stack* stack)
{
	if (!stack)
		return;

	if (stack->idx - 1 < -1)
		return;

	stack->idx--;
}
user_input_map* top_input_map_in_stack(user_input_map_stack* stack)
{
	if (!stack)
		return nullptr;

	int8_t idx = stack->idx - 1;
	if (idx < 0)
		return nullptr;

	return &stack->input_maps[idx];
}
bool is_input_map_stack_empty(user_input_map_stack* stack)
{
	return (stack->idx == -1);
}
void clear_input_map_stack(user_input_map_stack* stack)
{
	if (!stack)
		return;

	memset(stack, 0, sizeof(user_input_map) * INPUT_MAP_COUNT);
}
/***************************************
*   END: USER INPUT MAP STACK IMPL     *
****************************************/

struct users_input_def
{
	float                user_key_timestamp[USER_COUNT][KEY_COUNT];
	user_input_map_stack user_input_map_stack[USER_COUNT];
	eventdef_queue       user_event_queue[USER_COUNT];
	uint8_t              user_keys_state[USER_COUNT][KEY_COUNT];
	uint8_t              user_keys_mods[USER_COUNT][KEY_COUNT];
	//float                user_key_value[USER_COUNT][KEY_COUNT];
	//key_handler_def      user_handlers[USER_COUNT][CMD_COUNT];
	//key_action_def  user_actions[USER_COUNT][KEY_COUNT];
	//key_axis_def    user_axes[USER_COUNT][KEY_COUNT];
};
users_input_def* users = nullptr;

struct user_input_def_return
{
	float                *keys_timestamp  = nullptr;
	uint8_t              *keys_state      = nullptr;
	uint8_t              *keys_mods       = nullptr;	
	user_input_map_stack *input_map_stack = nullptr;
	eventdef_queue       *event_queue     = nullptr;
	//float                *keys_value           = nullptr;
	//key_handler_def      *cmds_handlers        = nullptr;
	//key_action_def  *keys_actions   = nullptr;
	//key_axis_def    *keys_axes      = nullptr;
};

user_input_def_return get_user_input_detail(uint8_t in_user_idx)
{
	user_input_def_return user_input;

	if (!users || in_user_idx > 3)
		return user_input;

	user_input.keys_timestamp   = users->user_key_timestamp[in_user_idx];
	user_input.keys_state       = users->user_keys_state[in_user_idx];
	user_input.keys_mods        = users->user_keys_mods[in_user_idx];
	user_input.input_map_stack  = &users->user_input_map_stack[in_user_idx];
	user_input.event_queue      = &users->user_event_queue[in_user_idx];
	//user_input.keys_value       = users->user_key_value[in_user_idx];
	//user_input.cmds_handlers        = users->user_handlers[in_user_idx];
	//user_input.keys_actions   = users->user_actions[in_user_idx];
	//user_input.keys_axes      = users->user_axes[in_user_idx];

	return user_input;
}

bool is_user_return_valid(user_input_def_return* in_user_return)
{
	if (!in_user_return)
		return false;

	// any member of user_input_def_return will do the same we just picked events ;)
	return (in_user_return->event_queue);
}

void mouse_get_pos(float* outx, float* outy)
{
	if (outx)
		*outx = mouse_x;

	if (outy)
		*outy = mouse_y;
}

user_input_map* create_user_input_map()
{
	return (user_input_map*)mem_alloc("struct: user_input_map", sizeof(user_input_map));
}

bool push_input_map(uint8_t ininputuser, user_input_map* input_map)
{
	if (ininputuser > 3 || ininputuser < 0)
		return false;

	if (!users || !input_map)
		return false;

	add_input_map_to_stack(&users->user_input_map_stack[ininputuser], input_map);

	return true;

	//Array *imd_actionlayout = user_actionlayout[ininputuser];
	//Array *img_axislayout   = user_axislayout[ininputuser];
	//Array *mhd              = user_inputhandlers[ininputuser];
	//
	//if (img_axislayout || imd_actionlayout || mhd)
	//	return;
	//
	//const char* array_name = nullptr;
	//
	//switch (ininputuser)
	//{
	//case 0: array_name = "array_actionmap_user_0"; break;
	//case 1: array_name = "array_actionmap_user_1"; break;
	//case 2: array_name = "array_actionmap_user_2"; break;
	//case 3: array_name = "array_actionmap_user_3"; break;
	//}
	//user_actionlayout[ininputuser]  = array_create(array_name, ek_count, sizeof(actionmsgdef));
	//
	//switch (ininputuser)
	//{
	//case 0: array_name = "array_axismap_user_0"; break;
	//case 1: array_name = "array_axismap_user_1"; break;
	//case 2: array_name = "array_axismap_user_2"; break;
	//case 3: array_name = "array_axismap_user_3"; break;
	//}
	//user_axislayout[ininputuser]    = array_create(array_name, ek_count, sizeof(axismsgdef));
	//
	//switch (ininputuser)
	//{
	//case 0: array_name = "array_msghandler_user_0"; break;
	//case 1: array_name = "array_msghandler_user_1"; break;
	//case 2: array_name = "array_msghandler_user_2"; break;
	//case 3: array_name = "array_msghandler_user_3"; break;
	//}
	//user_inputhandlers[ininputuser] = array_create(array_name, inmsgcount, sizeof(msghandlerdef));
}

void pop_input_map(uint8_t ininputuser)
{
	if (ininputuser > 3 || ininputuser < 0)
		return;

	if (!users)
		return;

	remove_top_input_map_from_stack(&users->user_input_map_stack[ininputuser]);
}

void bind_action_msg(user_input_map* input_map, int16_t inkey, uint8_t inkeystate, uint16_t inmsgid, uint8_t inmods)
{
	//Array* actions = user_actionlayout[ininputuser];
	//if (!actions)
	//	return;
	//
	//actionmsgdef* msgdef = (actionmsgdef*)array_get(actions, inkey);
	//if (!msgdef)
	//	return;
	//
	//msgdef->msg[inkeystate][inmods] = inmsgid;

	if (!input_map)
		return;

	input_map->actions[inkey].cmd[inkeystate][inmods] = inmsgid;
}

void bind_axis_msg(user_input_map* input_map, int16_t inkey, uint16_t inmsgid, float inaxisvalue, uint8_t inmods)
{
	//Array* axes = user_axislayout[ininputuser];
	//if (!axes)
	//	return;
	//
	//axismsgdef* msgdef = (axismsgdef*)array_get(axes, inkey);
	//if (!msgdef)
	//	return;
	//
	//msgdef->msg[inmods] = inmsgid;
	//key_setvalue(ininputuser, inkey, inaxisvalue);

	if (!input_map)
		return;

	/*input_map->axes[inkey].cmd[inmods]   = inmsgid;
	input_map->axes[inkey].value[inmods] = inaxisvalue;*/

	input_map->axes[inkey].cmd   = inmsgid;
	input_map->axes[inkey].value = inaxisvalue;
}

void bind_action_handler(user_input_map* input_map, uint16_t inmsgid, void(*action_handler)())
{
	//Array* handlers = user_inputhandlers[ininputuser];
	//if (!handlers)
	//	return;
	//
	//msghandlerdef* handlerdef = (msghandlerdef*)array_get(handlers, inmsgid);
	//if (!handlerdef)
	//	return;
	//
	//handlerdef->handler.action_handler = action_handler;

	if (!input_map)
		return;

	input_map->handlers[inmsgid].action = action_handler;
}

void bind_axis_handler(user_input_map* input_map, uint16_t inmsgid, void(*axis_handler)(float))
{
	//Array* handlers = user_inputhandlers[ininputuser];
	//if (!handlers)
	//	return;
	//
	//msghandlerdef* handlerdef = (msghandlerdef*)array_get(handlers, inmsgid);
	//if (!handlerdef)
	//	return;
	//
	//handlerdef->handler.axis_handler = axis_handler;

	if (!input_map)
		return;

	input_map->handlers[inmsgid].axis = axis_handler;
}

void process_axes()
{
	user_input_def_return user;
	int8_t                useridx = 0;
	user_input_map*       input_map = nullptr;
	uint32_t              input_map_idx = 0;
	int8_t                key_mod = 0;
	int8_t                key_state = 0;
	key_handler_def       handler;
	uint32_t              cmd = 0;
	float                 value = 0.0f;

	for (int32_t user_idx = 0; user_idx < USER_COUNT; ++user_idx)
	{
		user = get_user_input_detail(useridx);

		if (!is_user_return_valid(&user))
			continue;


		input_map_idx = user.input_map_stack->idx - 1;
		if (input_map_idx < 0)
			continue;
		input_map = &user.input_map_stack->input_maps[input_map_idx];

		for (int32_t key = 0; key < ek_count; ++key)
		{
			key_state = user.keys_state[key];
			if (key_state <= keystate_released)
				continue;

			key_mod = user.keys_mods[key];
			cmd     = input_map->axes[key].cmd;
			value   = input_map->axes[key].value;

			handler = input_map->handlers[cmd];
			if (handler.axis)
			{
				handler.axis(value);
			}
		}
	}

	//Array* user_axes = nullptr;
    //Array* user_keydetail = nullptr;
    //Array* user_handlers = nullptr;
    //axismsgdef* axismsg = nullptr;
    //key_detail* kd = nullptr;
    //msghandlerdef* msghandler = nullptr;
	//while (useridx < 4)
	//{
	//	//user_axes = user_axislayout[useridx];
	//	//user_keydetail = users_keydetail[useridx];
	//	//user_handlers = user_inputhandlers[useridx];
	//
	//	//if (!user_axes || !user_keydetail || !user_handlers)
	//		//continue;
	//
	//	user = get_user_input_detail(useridx);
	//	if (!is_user_return_valid(&user))
	//	{
	//	    ++useridx;
	//		continue;
	//	}
	//
	//	input_map_idx = user.input_map_stack->idx - 1;
	//	if (input_map_idx < 0)
	//		continue;
	//	input_map = &user.input_map_stack->input_maps[input_map_idx];
	//
	//	for (int32_t key = 0; key < ek_count; ++key)
	//	{
	//
	//		//axismsg = (axismsgdef*)array_get(user_axes, key);
	//
	//		//if (!axismsg)
	//			//continue;
	//
	//		//kd = (key_detail*)array_get(user_keydetail, key);
	//
	//		//if (!kd)
	//			//continue;
	//
	//		//if (kd->state <= keystate_released)
	//			//continue;
	//
	//		key_state = user.keys_state[ek_count];
	//		if (key_state <= keystate_released)
	//			continue;
	//
	//		key_mod = user.keys_mods[ek_count];
	//		value   = user.keys_value[key];
	//		cmd     = input_map->axes[key].cmd;
	//
	//		handler = input_map->handlers[cmd];
	//		if (handler.axis)
	//		{
	//			handler.axis(value);
	//		}
	//
	//		//msghandler = (msghandlerdef*)array_get(user_handlers, axismsg->msg[kd->mods]);
	//		//if (msghandler && msghandler->handler.axis_handler)
	//		//{
	//		//	msghandler->handler.axis_handler(kd->value);
	//		//}
	//	}
	//
	//	++useridx;
	//}
}

/***************************************
*     END: USERINPUT.h HEADER IMPL     *
****************************************/



/**************************************
*    BEGIN: EVENT TYPE HANDLERS            *
***************************************/
typedef void(*eventtype_handler)(uint8_t useridx, eventdef* inev);
eventtype_handler eventtype_handlers[eventtype_count];

void kboard_event_handler(uint8_t useridx, eventdef* inev)
{
	if (!inev)
		return;

	//event_kboard* ev = &inev->kboard;
	//
	//
	//Array         *user_actions  = user_actionlayout[useridx];
	//Array         *user_handlers = user_inputhandlers[useridx];
	//actionmsgdef  *actionmsg     = nullptr;
	//msghandlerdef *msghandler    = nullptr;
	//uint16_t       msg           = 0;
	//
	//if (user_actions && user_handlers)
	//{
	//	actionmsg = (actionmsgdef*)array_get(user_actions, ev->key);
	//	if (actionmsg)
	//	{
	//		if (actionmsg->msg[keystate_repeated][ev->mods] && ev->state == keystate_pressed)
	//			msg = actionmsg->msg[keystate_repeated][ev->mods];
	//		else
	//			msg = actionmsg->msg[ev->state][ev->mods];
	//
	//		msghandler = (msghandlerdef*)array_get(user_handlers, msg);
	//		if (msghandler && msghandler->handler.action_handler)
	//		{
	//			msghandler->handler.action_handler();
	//		}
	//	}
	//}

	event_kboard* ev = &inev->kboard;
	
	//printf("key: %s | %s | %s \n", keyname(ev->key), keystatename(ev->state), modkeyname(ev->mods));

	user_input_def_return user = get_user_input_detail(useridx);
	if (!is_user_return_valid(&user))
		return;

	user_input_map* input_map = top_input_map_in_stack(user.input_map_stack);
	if (!input_map)
		return;

	key_action_def* user_actions = input_map->actions;

	uint32_t cmd = 0;
	if (user_actions[ev->key].cmd[keystate_repeated][ev->mods] && ev->state == keystate_pressed)
	{
		cmd = user_actions[ev->key].cmd[keystate_repeated][ev->mods];
	}
	else
	{
		cmd = user_actions[ev->key].cmd[ev->state][ev->mods];
	}

	key_handler_def handler = input_map->handlers[cmd];

	if (handler.action)
	{
		handler.action();
	}
}

void mouse_event_handler(uint8_t useridx, eventdef* inev)
{
	if (!inev)
		return;

	event_mouse* ev = &inev->mouse;

	//printf("button: %s | %s | %s \n", keyname(ev->button), keystatename(ev->state), modkeyname(ev->mods));

	// loop through user_0 action map and invoke if nay

	// or

	// collect actions from user_0 
}

void gpad_event_handler(uint8_t useridx, eventdef* inev)
{
	//if (!inev)
	//	return;
	//
	//event_gpad* ev = &inev->gpad;
	//
	//printf("Controller[ %d ]: %s | %s \n", useridx, keyname(ev->button), keystatename(ev->state)/*, ev->value*/);
	//
	//Array* user_actions = user_actionlayout[useridx];
	//Array* user_handlers = user_inputhandlers[useridx];
	//actionmsgdef* actionmsg = nullptr;
	//msghandlerdef* msghandler = nullptr;
	//uint16_t       msg = 0;
	//
	//if (user_actions && user_handlers)
	//{
	//	actionmsg = (actionmsgdef*)array_get(user_actions, ev->button);
	//	if (actionmsg)
	//	{
	//		if (actionmsg->msg[keystate_repeated][emodkey_unknown] && ev->state == keystate_pressed)
	//			msg = actionmsg->msg[keystate_repeated][emodkey_unknown];
	//		else
	//			msg = actionmsg->msg[ev->state][emodkey_unknown];
	//
	//		msghandler = (msghandlerdef*)array_get(user_handlers, msg);
	//		if (msghandler && msghandler->handler.action_handler)
	//		{
	//			msghandler->handler.action_handler();
	//		}
	//	}
	//}

	event_gpad* ev = &inev->gpad;


	user_input_def_return user = get_user_input_detail(useridx);
	if (!is_user_return_valid(&user))
		return;

	user_input_map* input_map = top_input_map_in_stack(user.input_map_stack);
	if (!input_map)
		return;

	key_action_def* user_actions = input_map->actions;

	//printf("Controller[ %d ]: %s | %s  | %.2f\n", useridx, keyname(ev->button), keystatename(ev->state), input_map->axes[ev->button].value);
	
	uint32_t cmd = 0;
	if (user_actions[ev->button].cmd[keystate_repeated][emodkey_unknown] && ev->state == keystate_pressed)
	{
		cmd = user_actions[ev->button].cmd[keystate_repeated][emodkey_unknown];
	}
	else
	{
		cmd = user_actions[ev->button].cmd[ev->state][emodkey_unknown];
	}

	key_handler_def handler = input_map->handlers[cmd];

	if (handler.action)
	{
		handler.action();
	}
}
/**************************************
*    END: EVENT TYPE HANDLERS              *
***************************************/




/***************************************
*     BEGIN: EVENT.h HEADER IMPL       *
****************************************/
bool event_init()
{
	//user_eventqueue[0] = queue_create("array_eventqueue_user0", 64, sizeof(eventdef));
	//user_eventqueue[1] = queue_create("array_eventqueue_user1", 64, sizeof(eventdef));
	//user_eventqueue[2] = queue_create("array_eventqueue_user2", 64, sizeof(eventdef));
	//user_eventqueue[3] = queue_create("array_eventqueue_user3", 64, sizeof(eventdef));
	//
	//users_keydetail[0] = array_create("array_keydetail_user0", 256, sizeof(key_detail));
	//users_keydetail[1] = array_create("array_keydetail_user1", 256, sizeof(key_detail));
	//users_keydetail[2] = array_create("array_keydetail_user2", 256, sizeof(key_detail));
	//users_keydetail[3] = array_create("array_keydetail_user3", 256, sizeof(key_detail));
	//
	//for (int32_t useridx = 0; useridx < 4; ++useridx)
	//{
	//	if (!users_keydetail[useridx] || !user_eventqueue[useridx])
	//	{
	//		return false;
	//	}
	//}

	users = (users_input_def*)mem_alloc("users_input_details", sizeof(users_input_def));

	eventtype_handlers[eventtype_kboard] = kboard_event_handler;
	eventtype_handlers[eventtype_mouse]  = mouse_event_handler;
	eventtype_handlers[eventtype_gpad]   = gpad_event_handler;

	input_debugging_stuff_init();

	return true;
}

void onevent_kboard(int16_t inkey, int8_t instate, int8_t inmods)
{
	//if (inuserid < 0 || inuserid > 3)
	//	return;
	//
	//Queue   *ev_queue = user_eventqueue[inuserid];
	//key_detail *kd    = keydetail_get(inuserid, inkey);
	//
	//if (!kd)
	//	return;
	//
	//kd->state     = instate;
	//kd->mods      = inmods;
	//kd->timestamp = time_get_seconds();
	//
	//if (!ev_queue)
	//	return;
	//
	//eventdef ev;
	//ev.type         = eventtype_kboard;
	//ev.kboard.key   = inkey;
	//ev.kboard.state = instate;
	//ev.kboard.mods  = inmods;
	//
	//queue_add(ev_queue, &ev);

	user_input_def_return user = get_user_input_detail(0);
	if (!is_user_return_valid(&user))
		return;

	user.keys_state[inkey]     = instate;
	user.keys_mods[inkey]      = inmods;
	user.keys_timestamp[inkey] = time_get_seconds();

	eventdef ev;
    ev.type         = eventtype_kboard;
    ev.kboard.key   = inkey;
    ev.kboard.state = instate;
    ev.kboard.mods  = inmods;

	add_event_to_queue(user.event_queue, &ev);
}

void onevent_mouse_button(int16_t inbutton, int8_t instate, int8_t inmods)
{
	//if (inuserid < 0 || inuserid > 3)
	//	return;
	//
	//Queue      *ev_queue = user_eventqueue[inuserid];
	//key_detail *kd       = keydetail_get(inuserid, inbutton);
	//
	//if (!kd)
	//	return;
	//
	//double timestamp = 
	//
	//kd->state     = instate;
	//kd->mods      = inmods;
	//kd->timestamp = time_get_seconds();
	//
	//if (!ev_queue)
	//	return;
	//
	//eventdef ev;
	//ev.type         = eventtype_mouse;
	//ev.mouse.button = inbutton;
	//ev.mouse.state  = kd->state;
	//ev.mouse.mods   = kd->mods;
	//
	//queue_add(ev_queue, &ev);

	user_input_def_return user = get_user_input_detail(0);
	if (!is_user_return_valid(&user))
		return;

	user.keys_state[inbutton]     = instate;
	user.keys_mods[inbutton]      = inmods;
	user.keys_timestamp[inbutton] = time_get_seconds();

	eventdef ev;
	ev.type         = eventtype_mouse;
	ev.mouse.button = inbutton;
	ev.mouse.state  = instate;
	ev.mouse.mods   = inmods;

	add_event_to_queue(user.event_queue, &ev);
}

void onevent_gpad_button(int8_t inuserid, int16_t inbutton, int8_t instate)
{
	//if (inuserid < 0 || inuserid > 3)
	//	return;
	//
	//Queue* ev_queue = user_eventqueue[inuserid];
	//key_detail* kd = keydetail_get(inuserid, inbutton);
	//
	//if (!kd)
	//	return;
	//
	//kd->state = instate;
	//kd->timestamp = time_get_seconds();
	//
	//if (!ev_queue)
	//	return;
	//
	//eventdef ev;
	//ev.type        = eventtype_gpad;
	//ev.gpad.button = inbutton;
	//ev.gpad.state  = instate;
	//ev.gpad.userid = inuserid;
	//
	//queue_add(ev_queue, &ev);

	user_input_def_return user = get_user_input_detail(inuserid);
	if (!is_user_return_valid(&user))
		return;

	user.keys_state[inbutton]     = instate;
	user.keys_timestamp[inbutton] = time_get_seconds();

	eventdef ev;
	ev.type        = eventtype_gpad;
	ev.gpad.button = inbutton;
	ev.gpad.state  = instate;
	ev.gpad.userid = inuserid;

	add_event_to_queue(user.event_queue, &ev);
}

void onevent_gpad_axis(int8_t inuserid, int16_t inaxis, float invalue)
{
	//if (inuserid < 0 || inuserid > 3)
	//	return;
	//
	////Queue* ev_queue = user_eventqueue[inuserid];
	//key_detail* kd = keydetail_get(inuserid, inaxis);
	//
	//if (!kd)
	//	return;
	//
	//kd->value = invalue;
	//user.keys_value[inaxis] = invalue;

	user_input_def_return user = get_user_input_detail(inuserid);
	if (!is_user_return_valid(&user))
		return;

	user_input_map *input_map = top_input_map_in_stack(user.input_map_stack);
	if (!input_map)
		return;

	input_map->axes[inaxis].value = invalue;
}

void onevent_mouse_move(float inx, float iny)
{
	mouse_x = inx;
	mouse_y = iny;
}

void event_process()
{
	//process_axes();
	//
	//eventdef      *ev         = nullptr;
	//event_handler  ev_handler = nullptr;
	//Queue         *ev_queue   = nullptr;
	//
	//for (uint8_t queueidx = 0; queueidx < 4; ++queueidx)
	//{
	//	ev_queue = user_eventqueue[queueidx];
	//
	//	if (!ev_queue)
	//		return;
	//	
	//	while (queue_size(ev_queue))
	//	{
	//		ev = (eventdef*)queue_get(ev_queue);
	//
	//		if (!ev)
	//			return;
	//
	//		if (ev->type == eventtype_unknown || ev->type > eventtype_count - 1)
	//			return;
	//
	//		ev_handler = event_handlers[ev->type];
	//		if (ev_handler)
	//		{
	//			ev_handler(queueidx, ev);
	//		}
	//	}
	//
	//	queue_clear(ev_queue);
	//}

	process_axes();

	user_input_def_return  user;
	eventdef              *ev = nullptr;
	eventtype_handler      event_handler = NULL;

	for (uint8_t user_idx = 0; user_idx < USER_COUNT; ++user_idx)
	{
		user = get_user_input_detail(user_idx);

		if (!is_user_return_valid(&user))
			continue;

		while (!is_event_queue_empty(user.event_queue))
		{
			ev = get_event_from_queue(user.event_queue);
			
			event_handler = eventtype_handlers[ev->type];
			if (event_handler)
			{
				event_handler(user_idx, ev);
			}
		}

		clear_event_queue(user.event_queue);
	}
}
/***************************************
*       END: EVENT.h HEADER IMPL       *
****************************************/








