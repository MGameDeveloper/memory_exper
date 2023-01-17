#pragma once

enum ekeystate
{
	keystate_unknown,

	keystate_released,
	keystate_pressed,
	keystate_repeated,
	keystate_doubleclick,

	keystate_count
};

enum emodkeys
{
	emodkey_unknown,

	emodkey_shift = 1 << 0,
	emodkey_alt   = 1 << 1,
	emodkey_ctrl  = 1 << 2,

	emodkey_count = (emodkey_alt | emodkey_ctrl | emodkey_shift) + 1
};

enum ekeys
{
	ek_unknown = -1,

	// not done
	ek_cross, 
	ek_circle, 
	ek_triangle, 
	ek_square,
	ek_dpadup, 
	ek_dpaddown, 
	ek_dpadleft, 
	ek_dpadright,
	ek_L1, 
	ek_L2, 
	ek_L3, 
	ek_R1, 
	ek_R2, 
	ek_R3,
	ek_start,
	ek_select,
	ek_lanalogup,
	ek_lanalogdown,
	ek_lanalogright,
	ek_lanalogleft,
	ek_ranalogup,
	ek_ranalogdown,
	ek_ranalogright,
	ek_ranalogleft,

	ek_anykey, // not virtual key to map to

	ek_lmouse,
	ek_rmouse,
	ek_mmouse,

	ek_mouse_scrollup, // no virtual key to map to
	ek_mouse_scrolldown, // no virtual key to map to

	ek_a, 
	ek_b, 
	ek_c, 
	ek_d, 
	ek_e, 
	ek_f, 
	ek_g, 
	ek_h, 
	ek_i, 
	ek_j, 
	ek_k, 
	ek_l, 
	ek_m, 
	ek_n, 
	ek_o, 
	ek_p, 
	ek_q, 
	ek_r, 
	ek_s, 
	ek_t, 
	ek_u, 
	ek_v, 
	ek_w, 
	ek_x, 
	ek_y, 
	ek_z,

	ek_0,
	ek_1,
	ek_2,
	ek_3,
	ek_4,
	ek_5,
	ek_6,
	ek_7,
	ek_8,
	ek_9,

	ek_numpad0,
	ek_numpad1,
	ek_numpad2,
	ek_numpad3,
	ek_numpad4,
	ek_numpad5,
	ek_numpad6,
	ek_numpad7,
	ek_numpad8,
	ek_numpad9,

	ek_up,
	ek_down,
	ek_left,
	ek_right,

	ek_enter,
	ek_esc,
	ek_space,
	ek_backspace,
	ek_delete,
	ek_insert,
	ek_tab,
	ek_capslock,
	ek_numlock,
	ek_pageup,
	ek_pagedown,
	ek_end,
	ek_home,

	ek_slash,
	ek_backslash,
	ek_hyphen,
	ek_decimal,
	ek_semicolon,
	ek_tilde,
	ek_quote,
	ek_comma,
	ek_period,
	ek_left_bracket,
	ek_right_bracket,

	ek_multiply,
	ek_subtract,
	ek_add,
	ek_divide,
	ek_equals,

	ek_f1, 
	ek_f2,
	ek_f3,
	ek_f4,
	ek_f5,
	ek_f6,
	ek_f7,
	ek_f8,
	ek_f9,
	ek_f10,
	ek_f11,
	ek_f12,

	ek_count,
};