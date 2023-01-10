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
extern void  mem_display_info();

// simple macro to hide casting when passing memory pointer to delete and free its content
#define mem_ptr(var) (void**)&var


// may not be a good idea since all reterived pointers will be pointing the same block
// and can change its fields which may cause problems
// may consider removing this functionality
//extern void  mem_free_name(const char* Name); 


/************************************************
*                USAGE EXAMPLE                  *
************************************************/
/*

struct example_data
{
	const char* tag   = nullptr;
	float       data0 = 0.0f;
	uint32_t    data1 = 0;
	char        data2 = '\0';
};

	// Initialize memory with needed size
	if (!mem_init(MEM_SIZE_MB(1)))
	{
		printf("error: memory couldn't be initialize\n");
	}

	// Allocate variable by name and getting the memory pointer to it
	example_data* var0 = (example_data*)mem_alloc("var_name_0", sizeof(example_data));
	if (var0)
	{
		var0->tag = "something";
		var0->data0 = 3.1459f;
		var0->data1 = 213;
		var0->data2 = 'L';
	}

	// Allocate variable by name
	mem_alloc("var_name_1", sizeof(example_data));

	// Getting memory prevously allocated by name
	example_data* var1 = (example_data*)mem_get("var_name_1");
	if (var1)
	{
		var1->tag = "something_1";
		var1->data0 = 0.5614;
		var1->data1 = 65;
		var1->data2 = 'M';
	}

	// Show current memory usage
	mem_display_info();

	// Free memeory by its pointer
	mem_free(mem_ptr(var0));

	// Free memory by its name
	// var1 sill pointing the memory and can change its fields
	// may consider removing this functionality
	mem_free_name("var_name_1"); 

	// Show current memory usage
	mem_display_info();
*/
