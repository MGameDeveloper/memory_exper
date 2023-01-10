#pragma once

#define WIN32_MEAN_AND_LEAN
#include <Windows.h>

extern bool win32_init();
extern void win32_run();
extern bool win32_closing();