#pragma once

#include <stdint.h>

struct Stack;

extern Stack*   stack_create(const char* InName, uint32_t InElementNum, uint32_t InSingleElementSize);
extern void     stack_destroy(Stack** InTargetStack);
extern uint32_t stack_size(Stack* InTargetStack);
extern void     stack_add(Stack* InTargetStack, void* InElement);
extern void*    stack_get(Stack* InTargetStack);
extern void     stack_clear(Stack* InTargetStack);


