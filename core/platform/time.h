#pragma once

// defined in each specific platform cpp. for example in win32.cpp
extern void   time_begin();
extern void   time_end();
extern double time_get_seconds();
extern double time_get_milliseconds();
extern double time_get_microseconds();
extern double time_get_dt_as_seconds(); 
extern double time_get_dt_as_milliseconds(); 
extern double time_get_dt_as_microseconds();