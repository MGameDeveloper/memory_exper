#include "Queue.h"

#include "../Memory.h"

struct Queue
{
	uint8_t* Address     = nullptr; // for use by AddQueueElement
	uint32_t ElementSize = 0; // single element size used for offseting when adding or getting a value
	uint32_t Capacity    = 0; // max element allowed to be added
	uint32_t Count       = 0; // how many added;
	uint32_t GetIdx      = 0;
};

Queue* queue_create(const char* InName, uint32_t InElementNum, uint32_t InSingleElementSize)
{
	Queue* Q   = (Queue*)mem_alloc(InName, sizeof(Queue) + (InElementNum * InSingleElementSize) );

	if (!Q)
		return nullptr;

	Q->Address     = (uint8_t*)Q + sizeof(Queue);
	Q->ElementSize = InSingleElementSize;
	Q->Capacity    = InElementNum;
	Q->Count       = 0;

	return Q;
}

void queue_destroy(Queue** InTargetQueue)
{
	if (!InTargetQueue && !(*InTargetQueue)) return;

	Queue* Q = (*InTargetQueue);
	memset(Q, 0, sizeof(Queue) + (Q->Capacity * Q->ElementSize));

	mem_free((void**)Q);
	*InTargetQueue = nullptr;
}

uint32_t queue_size(Queue* InTargetQueue)
{
	if (!InTargetQueue) return 0;

	return (InTargetQueue->Count - InTargetQueue->GetIdx);
}

void  queue_add(Queue* InTargetQueue, void* InElement)
{
	//  queue is not valid or element is not valid.
	if (!InTargetQueue || !InElement) return; 

	// queue is full .
	if (InTargetQueue->Count >= InTargetQueue->Capacity) return; 
    
	// Base Address plus element offset to be added
	uint8_t* address = InTargetQueue->Address + (InTargetQueue->Count * InTargetQueue->ElementSize);
	InTargetQueue->Count++;

	memcpy(address, InElement, InTargetQueue->ElementSize);
}

void* queue_get(Queue* InTargetQueue)
{
	if (!InTargetQueue || !InTargetQueue->Address) return nullptr;

	if (InTargetQueue->GetIdx >= InTargetQueue->Count)
	{
		// clear since all queued items have been queried.
		
		// Clear Buffer: should we need this ????
		// memset(InTargetQueue->Address, 0, InTargetQueue->Capacity * InTargetQueue->ElementSize);

		// reset buffer data
		InTargetQueue->Count  = 0;
		InTargetQueue->GetIdx = 0;

		return nullptr;
	}

	uint32_t ElementOffset = InTargetQueue->GetIdx * InTargetQueue->ElementSize;
	uint8_t* Element       = InTargetQueue->Address + ElementOffset;
	
	InTargetQueue->GetIdx++;

	return Element;
}

void  queue_clear(Queue* InTargetQueue)
{
	if (!InTargetQueue || !InTargetQueue->Address) return;

	// Should we clear the Buffer ???
	// Clearing the buffer cause all pointers to the buffer to have no useful data.
	memset(InTargetQueue->Address, 0, InTargetQueue->Capacity * InTargetQueue->ElementSize);
	InTargetQueue->Count  = 0;
	InTargetQueue->GetIdx = 0;
}

