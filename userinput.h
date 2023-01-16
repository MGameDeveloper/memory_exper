#pragma once

#include <stdint.h>
#include "keys.h"

// defined int event.cpp
extern void keyvalue_set(int8_t inuseridx, int16_t inkey, float invalue);
extern void mouse_get_pos(float* outx, float* outy);