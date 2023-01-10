#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdint.h>

#define MEM_SIZE_KB(V) (V * 1024LL)
#define MEM_SIZE_MB(V) (MEM_SIZE_KB(V) * 1024LL)
#define MEM_SIZE_GB(V) (MEM_SIZE_MB(V) * 1024LL)
#define MEM_SIZE_TB(V) (MEM_SIZE_GB(V) * 1024LL)

extern bool  mem_init(uint32_t InSize);
extern void* mem_alloc(const char* Name, uint32_t InSize);
extern void* mem_get(const char* Name);
extern void  mem_free(void** InPtr);
extern void  mem_free_name(const char* Name);
extern void  mem_display_info();
