#include <Windows.h> // must be included otherwise including xinput.h will cause error: "No Target Architecture"
#include <stdlib.h> // for abs()
#include <Xinput.h>
#include "xinput_interface.h"
#include "../core/event/event.h"
#include "../keys.h"
#include "../time.h"

#pragma comment(lib, "xinput.lib")

enum egamepadkey
{
	egk_cross,
	egk_circle,
	egk_triangle,
	egk_square,
	egk_dpadup,
	egk_dpaddown,
	egk_dpadleft,
	egk_dpadright,
	egk_L1,
	egk_L2,
	egk_L3,
	egk_R1,
	egk_R2,
	egk_R3,
	egk_start,
	egk_select,
	egk_lanalogup,
	egk_lanalogdown,
	egk_lanalogright,
	egk_lanalogleft,
	egk_ranalogup,
	egk_ranalogdown,
	egk_ranalogright,
	egk_ranalogleft,

	egk_count
};
static int16_t controllerkeymap[egk_count];

struct controllerdef
{
	struct statedef
	{
		struct axesdef
		{
			float lanalog_x = 0.0f;
			float lanalog_y = 0.0f;
			float ranalog_x = 0.0f;
			float ranalog_y = 0.0f;
			float l2 = 0.0f;
			float r2 = 0.0f;
		};

		float   buttons_repeat_counter[egk_count];
		axesdef axes;
		bool    buttons[egk_count];
	};

	statedef state;
	DWORD    laststate = 0;
	bool     should_be_updated = true;
};
controllerdef controllers[4];

XINPUT_STATE    xinput_state;
DWORD           is_gamepad_connected      = 0;
XINPUT_GAMEPAD* xinput_gamepad            = nullptr;
controllerdef*  controller                = nullptr;
float           button_repeat_init_value  = 0.3f;
float           button_repeat_delay_value = 0.1f;
bool            xinput_buttons[egk_count];


void controller_vibrate_start(uint8_t ininputuser, uint16_t inleftmotorspeed, uint16_t inrightmotorspeed)
{
	if (ininputuser < 0 || ininputuser > 3)
		return;

	if (!controllers[ininputuser].should_be_updated)
		return;

	XINPUT_VIBRATION xinput_vibration;
	xinput_vibration.wLeftMotorSpeed = inleftmotorspeed;
	xinput_vibration.wRightMotorSpeed = inrightmotorspeed;

	XInputSetState(ininputuser, &xinput_vibration);
}

void controller_vibrate_end(uint8_t ininputuser)
{
	if (ininputuser < 0 || ininputuser > 3)
		return;

	if (!controllers[ininputuser].should_be_updated)
		return;

	XINPUT_VIBRATION xinput_vibration;
	xinput_vibration.wLeftMotorSpeed = 0;
	xinput_vibration.wRightMotorSpeed = 0;

	XInputSetState(ininputuser, &xinput_vibration);
}


void xinput_init()
{
	controllerkeymap[egk_cross] = ek_cross;
	controllerkeymap[egk_circle] = ek_circle;
	controllerkeymap[egk_triangle] = ek_triangle;
	controllerkeymap[egk_square] = ek_square;
	controllerkeymap[egk_dpadup] = ek_dpadup;
	controllerkeymap[egk_dpaddown] = ek_dpaddown;
	controllerkeymap[egk_dpadleft] = ek_dpadleft;
	controllerkeymap[egk_dpadright] = ek_dpadright;
	controllerkeymap[egk_L1] = ek_L1;
	controllerkeymap[egk_L2] = ek_L2;
	controllerkeymap[egk_L3] = ek_L3;
	controllerkeymap[egk_R1] = ek_R1;
	controllerkeymap[egk_R2] = ek_R2;
	controllerkeymap[egk_R3] = ek_R3;
	controllerkeymap[egk_start] = ek_start;
	controllerkeymap[egk_select] = ek_select;
	controllerkeymap[egk_lanalogup] = ek_lanalogup;
	controllerkeymap[egk_lanalogdown] = ek_lanalogdown;
	controllerkeymap[egk_lanalogright] = ek_lanalogright;
	controllerkeymap[egk_lanalogleft] = ek_lanalogleft;
	controllerkeymap[egk_ranalogup] = ek_ranalogup;
	controllerkeymap[egk_ranalogdown] = ek_ranalogdown;
	controllerkeymap[egk_ranalogright] = ek_ranalogright;
	controllerkeymap[egk_ranalogleft] = ek_ranalogleft;

	memset(xinput_buttons, 0, sizeof(bool) * egk_count);
	memset(&xinput_state, 0, sizeof(XINPUT_STATE));
}

float normalize_axis_value(int16_t inaxis)
{
	float normalized_value = (inaxis <= 0) ? 32768.f : 32767.f;
	return ((float)inaxis / normalized_value);
}

float get_controller_axis_value(int16_t inaxis, float innormalizedaxis, int16_t inaxisdeadzone)
{
	if (abs(inaxis) > inaxisdeadzone)
	{
		return innormalizedaxis;
	}

	return 0.0f;
}

void xinput_process()
{
	for (uint8_t useridx = 0; useridx < 4; ++useridx)
	{
		controller = &controllers[useridx];

		if (!controller->should_be_updated)
			continue;

		is_gamepad_connected = XInputGetState(useridx, &xinput_state);
		if (is_gamepad_connected != 0)
			controller->should_be_updated = false;

		if (controller->laststate == xinput_state.dwPacketNumber) // state has not changed since last time queried
			continue;

		xinput_gamepad = &xinput_state.Gamepad;

		xinput_buttons[egk_cross] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_A;
		xinput_buttons[egk_circle] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_B;
		xinput_buttons[egk_triangle] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_Y;
		xinput_buttons[egk_square] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_X;
		xinput_buttons[egk_dpadup] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_DPAD_UP;
		xinput_buttons[egk_dpaddown] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		xinput_buttons[egk_dpadleft] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		xinput_buttons[egk_dpadright] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		xinput_buttons[egk_L1] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		xinput_buttons[egk_L3] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		xinput_buttons[egk_R1] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		xinput_buttons[egk_R3] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		xinput_buttons[egk_start] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_START;
		xinput_buttons[egk_select] = xinput_gamepad->wButtons & XINPUT_GAMEPAD_BACK;
		xinput_buttons[egk_L2] = xinput_gamepad->bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		xinput_buttons[egk_R2] = xinput_gamepad->bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
		xinput_buttons[egk_lanalogup] = xinput_gamepad->sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		xinput_buttons[egk_lanalogdown] = xinput_gamepad->sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		xinput_buttons[egk_lanalogright] = xinput_gamepad->sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		xinput_buttons[egk_lanalogleft] = xinput_gamepad->sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		xinput_buttons[egk_ranalogup] = xinput_gamepad->sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		xinput_buttons[egk_ranalogdown] = xinput_gamepad->sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		xinput_buttons[egk_ranalogright] = xinput_gamepad->sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		xinput_buttons[egk_ranalogleft] = xinput_gamepad->sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

		onevent_gpad_axis(useridx, controllerkeymap[egk_lanalogup], get_controller_axis_value(xinput_gamepad->sThumbLY, normalize_axis_value(xinput_gamepad->sThumbLY), XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_lanalogdown], get_controller_axis_value(xinput_gamepad->sThumbLY, normalize_axis_value(xinput_gamepad->sThumbLY), XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_lanalogleft], get_controller_axis_value(xinput_gamepad->sThumbLX, normalize_axis_value(xinput_gamepad->sThumbLX), XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_lanalogright], get_controller_axis_value(xinput_gamepad->sThumbLX, normalize_axis_value(xinput_gamepad->sThumbLX), XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_ranalogup], get_controller_axis_value(xinput_gamepad->sThumbRY, normalize_axis_value(xinput_gamepad->sThumbRY), XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_ranalogdown], get_controller_axis_value(xinput_gamepad->sThumbRY, normalize_axis_value(xinput_gamepad->sThumbRY), XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_ranalogleft], get_controller_axis_value(xinput_gamepad->sThumbRX, normalize_axis_value(xinput_gamepad->sThumbRX), XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_ranalogright], get_controller_axis_value(xinput_gamepad->sThumbRX, normalize_axis_value(xinput_gamepad->sThumbRX), XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE));
		onevent_gpad_axis(useridx, controllerkeymap[egk_L2], get_controller_axis_value(xinput_gamepad->bLeftTrigger, normalize_axis_value(xinput_gamepad->bLeftTrigger / 255.f), XINPUT_GAMEPAD_TRIGGER_THRESHOLD));
		onevent_gpad_axis(useridx, controllerkeymap[egk_R2], get_controller_axis_value(xinput_gamepad->bRightTrigger, normalize_axis_value(xinput_gamepad->bRightTrigger / 255.f), XINPUT_GAMEPAD_TRIGGER_THRESHOLD));

		double time_since_start = time_get_seconds();
		
		for (int8_t buttonidx = 0; buttonidx < egk_count; ++buttonidx)
		{
			if (!controller->state.buttons[buttonidx] && xinput_buttons[buttonidx])
			{
				onevent_gpad_button(useridx, controllerkeymap[buttonidx], keystate_pressed);
				
				controller->state.buttons_repeat_counter[buttonidx] = time_since_start + button_repeat_init_value;
			}

			else if (controller->state.buttons[buttonidx] && !xinput_buttons[buttonidx])
			{
				onevent_gpad_button(useridx, controllerkeymap[buttonidx], keystate_released);
			}

			else if (controller->state.buttons[buttonidx] && xinput_buttons[buttonidx])
			{
				if (controller->state.buttons_repeat_counter[buttonidx] <= time_since_start)
				{
					onevent_gpad_button(useridx, controllerkeymap[buttonidx], keystate_repeated);

					controller->state.buttons_repeat_counter[buttonidx] = time_since_start + button_repeat_delay_value;
				}
			}
		}

		memcpy(controller->state.buttons, xinput_buttons, sizeof(bool) * egk_count);
	}
}

void xinput_devices_changed()
{
	for (int8_t useridx = 0; useridx < 4; ++useridx)
	{
		controllers[useridx].should_be_updated = true;
	}
}