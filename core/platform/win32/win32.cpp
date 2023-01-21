#include <stdio.h>
#include "win32.h"
#include "../../utils/Memory.h"
#include "../../utils/Containers/Array.h"
#include "../../event/event.h"
#include "../../input/keys.h"
#include "xinput_interface.h"

bool win32_keymap_init()
{
	Array* keymap = (Array*)array_create("array_keymap", 256, sizeof(int16_t));

	if (!keymap)
		return false;

	ekeys ek = ek_unknown;

#define MAP_KEY(VK, EK) ek = EK; array_add(keymap, VK, &ek)
	MAP_KEY(VK_LBUTTON, ek_lmouse);
	MAP_KEY(VK_RBUTTON, ek_rmouse);
	MAP_KEY(VK_MBUTTON, ek_mmouse);

	MAP_KEY('A', ek_a);
	MAP_KEY('B', ek_b);
	MAP_KEY('C', ek_c);
	MAP_KEY('D', ek_d);
	MAP_KEY('E', ek_e);
	MAP_KEY('F', ek_f);
	MAP_KEY('G', ek_g);
	MAP_KEY('H', ek_h);
	MAP_KEY('I', ek_i);
	MAP_KEY('J', ek_j);
	MAP_KEY('K', ek_k);
	MAP_KEY('L', ek_l);
	MAP_KEY('M', ek_m);
	MAP_KEY('N', ek_n);
	MAP_KEY('O', ek_o);
	MAP_KEY('P', ek_p);
	MAP_KEY('Q', ek_q);
	MAP_KEY('R', ek_r);
	MAP_KEY('S', ek_s);
	MAP_KEY('T', ek_t);
	MAP_KEY('U', ek_u);
	MAP_KEY('V', ek_v);
	MAP_KEY('W', ek_w);
	MAP_KEY('X', ek_x);
	MAP_KEY('Y', ek_y);
	MAP_KEY('Z', ek_z);
	MAP_KEY('0', ek_0);
	MAP_KEY('1', ek_1);
	MAP_KEY('2', ek_2);
	MAP_KEY('3', ek_3);
	MAP_KEY('4', ek_4);
	MAP_KEY('5', ek_5);
	MAP_KEY('6', ek_6);
	MAP_KEY('7', ek_7);
	MAP_KEY('8', ek_8);
	MAP_KEY('9', ek_9);

	MAP_KEY(VK_NUMPAD0, ek_numpad0);
	MAP_KEY(VK_NUMPAD1, ek_numpad1);
	MAP_KEY(VK_NUMPAD2, ek_numpad2);
	MAP_KEY(VK_NUMPAD3, ek_numpad3);
	MAP_KEY(VK_NUMPAD4, ek_numpad4);
	MAP_KEY(VK_NUMPAD5, ek_numpad5);
	MAP_KEY(VK_NUMPAD6, ek_numpad6);
	MAP_KEY(VK_NUMPAD7, ek_numpad7);
	MAP_KEY(VK_NUMPAD8, ek_numpad8);
	MAP_KEY(VK_NUMPAD9, ek_numpad9);

	MAP_KEY(VK_F1,  ek_f1);
	MAP_KEY(VK_F2,  ek_f2);
	MAP_KEY(VK_F3,  ek_f3);
	MAP_KEY(VK_F4,  ek_f4);
	MAP_KEY(VK_F5,  ek_f5);
	MAP_KEY(VK_F6,  ek_f6);
	MAP_KEY(VK_F7,  ek_f7);
	MAP_KEY(VK_F8,  ek_f8);
	MAP_KEY(VK_F9,  ek_f9);
	MAP_KEY(VK_F10, ek_f10);
	MAP_KEY(VK_F11, ek_f11);
	MAP_KEY(VK_F12, ek_f12);

	MAP_KEY(VK_UP,    ek_up);
	MAP_KEY(VK_DOWN,  ek_down);
	MAP_KEY(VK_LEFT,  ek_left);
	MAP_KEY(VK_RIGHT, ek_right);

	MAP_KEY(VK_RETURN,  ek_enter);
	MAP_KEY(VK_ESCAPE,  ek_esc);
	MAP_KEY(VK_SPACE,   ek_space);
	MAP_KEY(VK_BACK,    ek_backspace);
	MAP_KEY(VK_DELETE,  ek_delete);
	MAP_KEY(VK_INSERT,  ek_insert);
	MAP_KEY(VK_TAB,     ek_tab);
	MAP_KEY(VK_CAPITAL, ek_capslock);
	MAP_KEY(VK_NUMLOCK, ek_numlock);
	MAP_KEY(VK_PRIOR,   ek_pageup);
	MAP_KEY(VK_NEXT,    ek_pagedown);
	MAP_KEY(VK_END,     ek_end);
	MAP_KEY(VK_HOME,    ek_home);
	MAP_KEY(VK_DECIMAL, ek_decimal);

	MAP_KEY(VK_OEM_1,      ek_semicolon);
	MAP_KEY(VK_OEM_2,      ek_slash);
	MAP_KEY(VK_OEM_3,      ek_tilde);
	MAP_KEY(VK_OEM_4,      ek_left_bracket);
	MAP_KEY(VK_OEM_5,      ek_backslash);
	MAP_KEY(VK_OEM_6,      ek_right_bracket);
	MAP_KEY(VK_OEM_7,      ek_quote);
	MAP_KEY(VK_OEM_MINUS,  ek_hyphen);
	MAP_KEY(VK_OEM_PERIOD, ek_period);
	MAP_KEY(VK_OEM_PLUS,   ek_equals);
	MAP_KEY(VK_OEM_COMMA,  ek_comma);

	MAP_KEY(VK_MULTIPLY, ek_multiply);
	MAP_KEY(VK_SUBTRACT, ek_subtract);
	MAP_KEY(VK_ADD,      ek_add);
	MAP_KEY(VK_DIVIDE,   ek_divide);
	//MAP_KEY(VK_E,        ek_equals);
#undef MAP_KEY

	return true;
}

/***************************************
*         BEGIN: HELPER FUNCTION       *
****************************************/
int16_t keymap_get(uint16_t in_virtual_key)
{
	static Array* keymap = (Array*)mem_get("array_keymap");

	if (!keymap)
	{
		printf("win32.cpp: keymap_get(%d) failed to get [ array_keymap ] from memory\n", in_virtual_key);
		return ek_unknown;
	}
	
	if (in_virtual_key > 255 || in_virtual_key < 0)
	{
		printf("unknown key: %d\n", in_virtual_key);
		return ek_unknown;
	}
	
	int16_t key = *((int16_t*)array_get(keymap, in_virtual_key));

	return key;
}

int8_t modifiers_get()
{
	int8_t mod = emodkey_unknown;

	mod |= (GetAsyncKeyState(VK_CONTROL) & 0x8000) ? emodkey_ctrl  : emodkey_unknown;
	mod |= (GetAsyncKeyState(VK_SHIFT)   & 0x8000) ? emodkey_shift : emodkey_unknown;
	mod |= (GetAsyncKeyState(VK_MENU)    & 0x8000) ? emodkey_alt   : emodkey_unknown;

	return mod;
}
/***************************************
*         END: HELPER FUNCTION         *
****************************************/


/***************************************
*         BEGIN: TIME.H IMPL           *
****************************************/
struct timedef
{
	double frequency   = 0;
	double begin       = 0;
	double end         = 0;
	double elapsedtime = 0;
};
timedef win32_time;

LARGE_INTEGER large_integer;

void time_begin()
{
	QueryPerformanceCounter(&large_integer);
	win32_time.begin = double(large_integer.QuadPart);
}

void time_end()
{
	QueryPerformanceCounter(&large_integer);
	
	win32_time.end         = (double)large_integer.QuadPart;
	win32_time.elapsedtime = (win32_time.end - win32_time.begin) * win32_time.frequency;
}


double time_get_dt_as_seconds()
{
	return win32_time.elapsedtime;
}

double time_get_dt_as_milliseconds()
{
	return (win32_time.elapsedtime * 1000.f);
}

double time_get_dt_as_microseconds()
{
	return (win32_time.elapsedtime * 1000000.f);
}

double time_get_seconds()
{
	QueryPerformanceCounter(&large_integer);

	double time = (double)large_integer.QuadPart * win32_time.frequency;
	return time;
}

double time_get_milliseconds()
{
	QueryPerformanceCounter(&large_integer);

	double time = (double)large_integer.QuadPart * win32_time.frequency * 1000.f;
	return time;
}

double time_get_microseconds()
{
	QueryPerformanceCounter(&large_integer);

	double time = (double)large_integer.QuadPart * win32_time.frequency * 1000000.f;
	return time;
}

bool win32_time_init()
{
	if (!QueryPerformanceFrequency(&large_integer))
		return false;

	win32_time.frequency = 1.0f / (double)large_integer.QuadPart;

	return true;
}
/***************************************
*         END: TIME.H IMPL             *
****************************************/

LRESULT WndProc(HWND InHwnd, UINT InMsg, WPARAM InWParam, LPARAM InLParam)
{
	switch (InMsg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		DestroyWindow(InHwnd);
		return 0;

	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
	{
		WORD KeyFlags = HIWORD(InLParam);

		bool is_repeated = (KeyFlags & KF_REPEAT) == KF_REPEAT;
		bool is_released = (KeyFlags & KF_UP) == KF_UP;
		
		ekeystate keystate = keystate_unknown;
		
		if (is_released)
			keystate = keystate_released;
		else
		{
			if (is_repeated)
				keystate = keystate_repeated;
			else
				keystate = keystate_pressed;
		}
		
		onevent_kboard(0, keymap_get((uint16_t)InWParam), keystate, modifiers_get());
	}
	break;

	case WM_LBUTTONDOWN:
		onevent_mouse_button(0, ek_lmouse, keystate_pressed, modifiers_get());
		break;
	case WM_LBUTTONUP:
		onevent_mouse_button(0, ek_lmouse, keystate_released, modifiers_get());
		break;
	case WM_LBUTTONDBLCLK:
		onevent_mouse_button(0, ek_lmouse, keystate_doubleclick, modifiers_get());
		break;

	case WM_RBUTTONDOWN:
		onevent_mouse_button(0, ek_rmouse, keystate_pressed, modifiers_get());
		break;
	case WM_RBUTTONUP:
		onevent_mouse_button(0, ek_rmouse, keystate_released, modifiers_get());
		break;
	case WM_RBUTTONDBLCLK:
		onevent_mouse_button(0, ek_rmouse, keystate_doubleclick, modifiers_get());
		break;

	case WM_MBUTTONDOWN:
		onevent_mouse_button(0, ek_mmouse, keystate_pressed, modifiers_get());
		break;
	case WM_MBUTTONUP:
		onevent_mouse_button(0, ek_mmouse, keystate_released, modifiers_get());
		break;
	case WM_MBUTTONDBLCLK:
		onevent_mouse_button(0, ek_mmouse, keystate_doubleclick, modifiers_get());
		break;

	case WM_MOUSEWHEEL:
	{
		SHORT delta = GET_WHEEL_DELTA_WPARAM(InWParam);
		if (delta < 0)
			onevent_mouse_button(0, ek_mouse_scrolldown, keystate_pressed, modifiers_get());
		else
			onevent_mouse_button(0, ek_mouse_scrollup,   keystate_pressed, modifiers_get());
	}
		break;

	case WM_MOUSEMOVE:
	{
		float x = ((float)(short)LOWORD(InLParam));
		float y = ((float)(short)HIWORD(InLParam));
		onevent_mouse_move(x, y);
	}
		break;

	case WM_DEVICECHANGE:
		xinput_devices_changed();
		break;
	}

	return DefWindowProc(InHwnd, InMsg, InWParam, InLParam);
};


struct win32data_s
{
	const wchar_t* wnd_class_name = nullptr;
	const wchar_t* wnd_title = nullptr;
	HWND hwnd = nullptr;
	HINSTANCE hinstance = nullptr;
	uint32_t x = 0;
	uint32_t y = 0;
	uint32_t w = 0;
	uint32_t h = 0;
	bool quit = false;
};

static win32data_s win32data;

bool win32_init()
{
	if (!win32_time_init())
	{
		printf("win32 time initialization failed.\n");
		return false;
	}

	// should memory initialization be in platform.cpp - platform_init()
	if (!mem_init(MEM_SIZE_MB(2)))
	{
		printf("memory initialization failed.\n");
		return false;
	}

	if (!win32_keymap_init())
	{
		printf("win32 keymap initialization failed.\n");
		return false;
	}

	if (!event_init())
	{
		printf("event system initialization failed.\n");
		return false;
	}

	xinput_init();

	win32data.hinstance      = GetModuleHandle(NULL);
	win32data.wnd_class_name = L"main_window";
	win32data.wnd_title      = L"MGameDev";
	win32data.x              = CW_USEDEFAULT;
	win32data.y              = CW_USEDEFAULT;
	win32data.w              = CW_USEDEFAULT;
	win32data.h              = CW_USEDEFAULT;
	win32data.quit           = false;

	WNDCLASS wc;
	memset(&wc, 0, sizeof(WNDCLASS));

	wc.lpfnWndProc   = WndProc;
	wc.lpszClassName = win32data.wnd_class_name;
	wc.hInstance     = win32data.hinstance;
	wc.style         = CS_DBLCLKS;

	RegisterClass(&wc);

	win32data.hwnd = 
		CreateWindow(win32data.wnd_class_name, win32data.wnd_title, WS_OVERLAPPEDWINDOW, win32data.x, win32data.y, win32data.w, win32data.h, NULL, NULL, win32data.hinstance, NULL);

	if (!win32data.hwnd)
		return false;

	ShowWindow(win32data.hwnd, 1);
	UpdateWindow(win32data.hwnd);

	printf("win32 platform initialized.\n");

	return true;
}

bool win32_deinit()
{
	mem_deinit();

	return true;
}

void win32_run()
{
	MSG msg;
	memset(&msg, 0, sizeof(MSG));

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
			win32data.quit = true;
		else
		{
			TranslateMessage(&msg);
			DispatchMessageW(&msg);
		}
	}

	xinput_process();
	event_process();
}

bool win32_closing()
{
	return win32data.quit;
}
