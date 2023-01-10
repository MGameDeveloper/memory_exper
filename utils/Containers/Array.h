#pragma once

#include <stdint.h>

struct Array;

extern Array*   array_create(const char* InName, uint32_t InElementNum, uint32_t InSingleElementSize);
extern void     array_destroy(Array** InTargetArray);
extern uint32_t array_size(Array* InTargetArray);
extern void     array_add(Array* InTargetArray, int32_t InIdx, void* InElement);
extern void*    array_get(Array* InTargetArray, int32_t InIdx);
extern void     array_clear(Array* InTargetArray);