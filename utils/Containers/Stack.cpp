#include "Stack.h"

#include "../Memory.h"

struct Stack
{
	uint8_t* Address     = nullptr;
	uint32_t Capacity    = 0;
	uint32_t Count       = 0;
	uint32_t ElementSize = 0;
};

Stack* stack_create(const char* InName, uint32_t InElementNum, uint32_t InSingleElementSize)
{
	Stack* S = (Stack*)mem_alloc(InName, InElementNum * InSingleElementSize);

	if (!S)
		return nullptr;

	S->Address     = (uint8_t*)S + sizeof(Stack);
	S->Capacity    = InElementNum;
	S->Count       = 0;
	S->ElementSize = InSingleElementSize;

	return S;
}

void stack_destroy(Stack** InTargetStack)
{
	if (!InTargetStack || !(*InTargetStack)) return;

	Stack* S = *InTargetStack;
	memset(S, 0, sizeof(Stack) + (S->Capacity * S->ElementSize));

	mem_free((void**)InTargetStack);
	
	*InTargetStack = nullptr;
}

uint32_t stack_size(Stack* InTargetStack)
{
	if (!InTargetStack) return 0;

	return InTargetStack->Count;
}

void stack_add(Stack* InTargetStack, void* InElement)
{
	if (!InTargetStack || !InElement) return;

	if (InTargetStack->Count >= InTargetStack->Capacity) return; 

	uint8_t* Address = InTargetStack->Address + (InTargetStack->ElementSize * InTargetStack->Count);
	InTargetStack->Count++;
	
	memcpy(Address, InElement, InTargetStack->ElementSize);
}

void* stack_get(Stack* InTargetStack)
{
	if (!InTargetStack) return nullptr;

	int32_t Idx = InTargetStack->Count - 1;
	if (Idx < 0)
		return nullptr;

	InTargetStack->Count--;

	return ( InTargetStack->Address + (Idx * InTargetStack->ElementSize) );
}

void stack_clear(Stack* InTargetStack)
{
	if (!InTargetStack || !InTargetStack->Address) return;

	memset(InTargetStack->Address, 0, (InTargetStack->Capacity * InTargetStack->ElementSize));
}