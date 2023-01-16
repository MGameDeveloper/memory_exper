#include "Memory.h"

#include <stdlib.h>
#include <cstring>
#include <cstdio>

struct Memory_s
{
	uint32_t Size = 0;
	uint8_t* Address = nullptr;
};

static Memory_s GMemory, GFreeMemory;

bool mem_init(uint32_t InSize)
{
	if (GMemory.Address)
	{
		printf("Memory already initialized with size: %d BYTE\n", GMemory.Size);
		return false;
	}

	if (InSize < MEM_SIZE_KB(1))
	{
		printf("mem_init( %d ). Provided size should be at least 1KB or greater.", InSize);
		return false;
	}

	GMemory.Size        = InSize;
	GMemory.Address     = (uint8_t*)malloc(InSize);
	GFreeMemory.Size    = GMemory.Size;
	GFreeMemory.Address = GMemory.Address;

	if (!GFreeMemory.Address)
	{
		printf("malloc failed to return valid memory\n");
		return false;
	}

	memset(GFreeMemory.Address, 0, GFreeMemory.Size);
	return true;
}

/*************************************************
*            EXPERIMENTAL FUNCTIONS
**************************************************/

/*********************************************
* CASES TO TEST 
*     @ Allocation from GFreeMemory
*     @ Allocation from Free Blocks
*         # Finding free block with exact size
*         # Splitting block that is enough for two allocations
*         # Merging two free blocks that are contigous as one block. only support to 2 contigous block may support looking for all
*             contigous block and merge them as one
*     @ Deallocation
*     @ Show Memory Usage
*********************************************/

struct memblkdef
{
	char       name[32];
	memblkdef* next = nullptr;
	memblkdef* prev = nullptr;
	uint8_t*   data = nullptr;
	uint32_t   size = 0;
};

struct memblklist
{
	memblkdef* head = nullptr;
	memblkdef* tail = nullptr;
};

struct memalloctrackerdef
{
	uint32_t alloccount = 0;
	uint32_t freecount = 0;
};


/*****************************************************
* BEGIN: HELPER FUNCTIONS
*****************************************************/
uint32_t str_size(const char* str)
{
	uint32_t len = 0;
	for (; *str != '\0'; ++str)
		++len;

	return len;
}

void detach_blk(memblkdef* blk, memblklist* list)
{
	if (blk->next && blk->prev)
	{
		blk->next->prev = blk->prev;
		blk->prev->next = blk->next;
	}
	else if (blk->next && !blk->prev)
	{
		list->head        = blk->next;
		list->head->prev  = nullptr;
		blk->next         = nullptr;
	}
	else if (!blk->next && blk->prev)
	{
		list->tail       = blk->prev;
		list->tail->next = nullptr;
		blk->prev        = nullptr;
	}
	else
	{
		list->head = nullptr;
		list->tail = nullptr;
	}
}

void attach_blk(memblkdef* blk, memblklist* list)
{
	if (!list->head)
	{
		list->head = blk;
		list->tail = blk;
		blk->prev  = nullptr;
		blk->next  = nullptr;
	}
	else
	{
		list->tail->next = blk;
		blk->prev        = list->tail;
		list->tail       = blk;
		blk->next        = nullptr;
	}
}

void merge_blk(memblkdef* blk, memblkdef* nextblk)
{
	blk->next = nextblk->next;

	if (nextblk->next)
		nextblk->next->prev = blk;

	blk->size = blk->size + sizeof(memblkdef) + nextblk->size;
	memset(blk->data, 0, blk->size);
}

// need to be checked it really split with keeping connection list in right way
memblkdef* split_blk(memblkdef* blk, uint32_t leftsize, uint32_t requstedsize)
{
	memblkdef* subblk = blk + sizeof(memblkdef) + leftsize;
	subblk->data      = (uint8_t*)subblk + sizeof(memblkdef);
	subblk->size      = requstedsize;
	memset(subblk->data, 0, subblk->size);

	blk->size = leftsize;

	return subblk;
}

void link_subblk_after(memblkdef* blk, memblkdef* subblk)
{
	if (!blk->next)
		subblk->next = nullptr;
	else
	{
		blk->next->prev = subblk;
		subblk->next    = blk->next;
	}

	subblk->prev = blk;
	blk->next    = subblk;
}
/*****************************************************
* END: HELPER FUNCTIONS
*****************************************************/

static memblklist         freeblks;
static memblklist         usedblks;
static memalloctrackerdef memalloctracker;


void* mem_alloc(const char* Name, uint32_t InSize)
{
	uint32_t blkheadersize = sizeof(memblkdef);
	uint32_t entireblksize = InSize + sizeof(memblkdef);

	uint32_t namelen = str_size(Name);
	if (namelen >= 32)
		namelen = 32;
	
	memblkdef* blk = nullptr;
	
	if (GFreeMemory.Size >= InSize && GFreeMemory.Address)
	{
		blk       = (memblkdef*)GFreeMemory.Address;
		blk->data = GFreeMemory.Address + blkheadersize;
		blk->size = InSize;
		
		attach_blk(blk, &usedblks);

		GFreeMemory.Address = blk->data + InSize;
		GFreeMemory.Size = GFreeMemory.Size - entireblksize;
	}
	else if (freeblks.head)
	{
		for (blk = freeblks.head; blk; blk = blk->next)
		{
			if (blk->size == InSize)
			{
				break;
			}
			else if (blk->size > (sizeof(memblkdef) + InSize))
			{
				// NOTE: Note Tested Yet

				uint32_t aftersplitsize = (blk->size) - (sizeof(memblkdef) + InSize);

				if (aftersplitsize < sizeof(uint32_t))
					continue;
				else
				{
					memblkdef* subblk = split_blk(blk, aftersplitsize, InSize);
					link_subblk_after(blk, subblk);
					blk = subblk;
					break;
				}
			}
		}

		if (blk)
		{
			// an empty block has been found that satisfied the requested size
			detach_blk(blk, &freeblks);
			attach_blk(blk, &usedblks);
		}
		else
		{
			// Looks for two contigous free blocks that their sum satisfies
			// the requested size 
			// Steps:
			//    1- search to contigouse free block that their size match requested size
			//    2- merge the two blocks
			//    3- detach the block from the freeblks linklist
			//    4- attach the block to the usedblks linklist
			//    5- return the block data to the user

			// Note: Note tested yet

			blk                = freeblks.head;
			memblkdef* nextblk = nullptr;

			uint32_t blksize     = blk->size;
			uint32_t nextblksize = 0;
			if (nextblk)
				nextblksize = sizeof(memblkdef) + nextblk->size;

			while (blk)
			{
				nextblk = blk->next;

				if (!blk && !nextblk) break;

				blksize     = blk->size;
				nextblksize = sizeof(memblkdef) + nextblk->size;

				if (blksize + nextblksize >= InSize) // enough size
				{
					// check if the two free blocks are contigous
					if (&(*(blk->data + blksize)) != &(*(uint8_t*)nextblk))
						continue;
					else
					{
						merge_blk(blk, nextblk);
						detach_blk(blk, &freeblks);
						attach_blk(blk, &usedblks);

						break;
					}
				}

				blk = nextblk;
			}
		}
	}
	else
	{
		printf("OUT OF MEMORY.\n");
	}

	if (!blk)
		return nullptr;

	memcpy(blk->name, Name, namelen);
	memalloctracker.alloccount++;

	return blk->data;
}

// need test
void mem_free(void** InPtr)
{
	if (!InPtr || !(*InPtr)) return;

	memblkdef* blk = usedblks.head;

	for (; blk ; blk = blk->next)
		if (blk->data == *InPtr)
			break;

	if (blk)
	{
		//================= STEPS ====================
		// --> Mark the block to be empty blok
		// --> Clear the block data
		// --> Detach The Block From Used Blocks
		// --> Attach The Block To Freed Blocks
		// --> Increase DeAllocation Counter

		//static const char* name = "EmptyBlock";
		//memcpy(blk->name, name, str_size(name));
		memset(blk->data, 0, blk->size);

		detach_blk(blk, &usedblks);
		attach_blk(blk, &freeblks);

		memalloctracker.freecount++;

		(*InPtr) = nullptr;
	}
}

void mem_display_info()
{
	// show total budget we have
	// show used space with header size calculated
	// show freed space with header size calculated
	// show how many allocation we made
	// show how many deallocation we made
	// show used blocks name with ther size and address  -> [blkname, size, address]
	// show free blocks name with their size and address -> [blkname, size, address]

	uint32_t UsedMemorySize = 0;
	uint32_t FreeMemorySize = GFreeMemory.Size;

	memblkdef* blk = usedblks.head;
	for (; blk; blk = blk->next)
		UsedMemorySize = UsedMemorySize + blk->size + sizeof(memblkdef);

	blk = freeblks.head;
	for (; blk; blk = blk->next)
		FreeMemorySize = FreeMemorySize + blk->size + sizeof(memblkdef);

	printf("\n************************************\n");
	printf("*       BEGIN: MEMORY INFO         *\n");
	printf("************************************\n");
	printf("- TOTAL MEMORY: %d BYTE\n", GMemory.Size);
	printf("- USED MEMORY:  %d BYTE\n", UsedMemorySize);
	printf("- FREE MEMORY:  %d BYTE\n", FreeMemorySize);
	printf("- ALLOC COUNT:  %d\n", memalloctracker.alloccount);
	printf("- FREE COUNT:   %d\n", memalloctracker.freecount);

	printf("\n[ USED MEMORY INFO ]\n");
	blk = usedblks.head;
	uint32_t i = 0;
	for (; blk; ++i, blk = blk->next)
		printf("\t%d -> [ %s ][ %d BYTE ][ %p ]\n", i, blk->name, blk->size, &(*blk->data));
	

	printf("\n[ FREED MEMORY INFO ]\n");
	blk = freeblks.head;
	i = 0;
	for (; blk; ++i, blk = blk->next)
		printf("\t%d -> [ %s ][ %d BYTE ][ %p ]\n", i, blk->name, blk->size, &(*blk->data));

	printf("************************************\n");
	printf("*        END: MEMORY INFO          *\n");
	printf("************************************\n");
}

void* mem_get(const char* Name)
{
	memblkdef* blk = usedblks.head;

	for (; blk; blk = blk->next)
		if (strcmp(blk->name, Name) == 0)
			break;

	if (!blk)
		return nullptr;

	return blk->data;
}


// not working need fix
extern bool mem_deinit()
{
	memblkdef *blk = usedblks.head;
	memblkdef* nextblk = nullptr;

	for (; blk; blk = nextblk)
	{
		nextblk = blk->next;

		memset(blk->data, 0, blk->size);

		detach_blk(blk, &usedblks);
		attach_blk(blk, &freeblks);

		memalloctracker.freecount++;
	}

	mem_display_info();

	if (GMemory.Address)
	{
		free(GMemory.Address);
		GMemory.Size = 0;

		GFreeMemory.Address = nullptr;
		GFreeMemory.Size    = 0;
	}

	return true;
}