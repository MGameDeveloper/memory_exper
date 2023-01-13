#include "win32.h"

#include "../common.h"

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

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
	
	MAP_KEY(VK_A, ek_a);
	MAP_KEY(VK_B, ek_b);
	MAP_KEY(VK_C, ek_c);
	MAP_KEY(VK_D, ek_d);
	MAP_KEY(VK_E, ek_e);
	MAP_KEY(VK_F, ek_f);
	MAP_KEY(VK_G, ek_g);
	MAP_KEY(VK_H, ek_h);
	MAP_KEY(VK_I, ek_i);
	MAP_KEY(VK_J, ek_j);
	MAP_KEY(VK_K, ek_k);
	MAP_KEY(VK_L, ek_l);
	MAP_KEY(VK_M, ek_m);
	MAP_KEY(VK_N, ek_n);
	MAP_KEY(VK_O, ek_o);
	MAP_KEY(VK_P, ek_p);
	MAP_KEY(VK_Q, ek_q);
	MAP_KEY(VK_R, ek_r);
	MAP_KEY(VK_S, ek_s);
	MAP_KEY(VK_T, ek_t);
	MAP_KEY(VK_U, ek_u);
	MAP_KEY(VK_V, ek_v);
	MAP_KEY(VK_W, ek_w);
	MAP_KEY(VK_X, ek_x);
	MAP_KEY(VK_Y, ek_y);
	MAP_KEY(VK_Z, ek_z);
	MAP_KEY(VK_0, ek_0);
	MAP_KEY(VK_1, ek_1);
	MAP_KEY(VK_2, ek_2);
	MAP_KEY(VK_3, ek_3);
	MAP_KEY(VK_4, ek_4);
	MAP_KEY(VK_5, ek_5);
	MAP_KEY(VK_6, ek_6);
	MAP_KEY(VK_7, ek_7);
	MAP_KEY(VK_8, ek_8);
	MAP_KEY(VK_9, ek_9);

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
	MAP_KEY(VK_E,        ek_equals);

#undef MAP_KEY

	return true;
}

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

	return *( (int16_t*)array_get(keymap, in_virtual_key) );
}

LRESULT WndProc(HWND InHwnd, UINT InMsg, WPARAM InWParam, LPARAM InLParam)
{
	event_key event;

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
		//WORD vKeyCode = (WORD)InWParam;
		WORD KeyFlags = HIWORD(InLParam);

		bool is_repeated = (KeyFlags & KF_REPEAT) == KF_REPEAT;
		bool is_released = (KeyFlags & KF_UP) == KF_UP;

		event.devicetype = inputdevice_kboard;
		event.key        = keymap_get(InWParam);
		
		ekeystate keystate = keystate_unknown;
		switch (is_repeated)
		{
		case 0:
			keystate = keystate_pressed;
			break;

		case 1:
			keystate = keystate_repeated;
			break;

		default:
			keystate = keystate_released;
		}
		event.state     = keystate;
		event.timestamp = 0.0;
	}
	break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		break;

	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		break;

	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_DEVICECHANGE:
		break;
	}

	if(event.devicetype != inputdevice_unknown)
		event_add(&event);

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
	if (!mem_init(MEM_SIZE_MB(2)))
	{
		printf("memory initialization failed.\n");
		return false;
	}

	if (!event_init())
	{
		printf("event system initialization failed.\n");
		return false;
	}

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

	if (!win32_keymap_init())
	{
		printf("win32 keymap initialization failed.\n");
		return false;
	}
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
}

bool win32_closing()
{
	return win32data.quit;
}