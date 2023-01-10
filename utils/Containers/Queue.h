#pragma once

#include <stdint.h>

struct Queue;

extern Queue*   queue_create(const char* InName, uint32_t InElementNum, uint32_t InSingleElementSize);
extern void     queue_destroy(Queue** InTargetQueue);
extern uint32_t queue_size(Queue* InTargetQueue);
extern void     queue_add(Queue* InTargetQueue, void* InElement);
extern void*    queue_get(Queue* InTargetQueue);
extern void     queue_clear(Queue* InTargetQueue);
