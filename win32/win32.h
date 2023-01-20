#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

// putting this in cpp file trigger an error "No Target Archeticture"
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

extern bool win32_init();
extern bool win32_deinit();
extern void win32_run();
extern bool win32_closing();