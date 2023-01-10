#include "Array.h"

#include "../Memory.h"

struct Array
{
	uint8_t* Address     = nullptr;
	uint32_t Capacity    = 0;
	uint32_t ElementSize = 0;
};

Array* array_create(const char* InName, uint32_t InElementNum, uint32_t InSingleElementSize)
{
	Array* A = (Array*)mem_alloc(InName, sizeof(Array) + (InElementNum * InSingleElementSize) );

	if (!A)
		return nullptr;

	A->Address     = (uint8_t*)A + sizeof(Array);
	A->Capacity    = InElementNum;
	A->ElementSize = InSingleElementSize;

	return A;
}

void array_destroy(Array** InTargetArray)
{
	if (!InTargetArray && !(*InTargetArray)) return;

	Array* A = *InTargetArray;
	memset(A, 0, sizeof(Array) + (A->Capacity * A->ElementSize));

	mem_free((void**)A);
	*InTargetArray = nullptr;
}

uint32_t array_size(Array* InTargetArray)
{
	if (!InTargetArray) return 0;

	return InTargetArray->Capacity;
}

void  array_add(Array* InTargetArray, int32_t InIdx, void* InElement)
{
	if (!InTargetArray || !InTargetArray->Address || !InElement) return;

	if (InIdx >= InTargetArray->Capacity || InIdx < 0) return;

	uint8_t* Element = InTargetArray->Address + (InTargetArray->ElementSize * InIdx);
	memcpy(Element, InElement, InTargetArray->ElementSize);
}

void* array_get(Array* InTargetArray, int32_t InIdx)
{
	if (!InTargetArray || !InTargetArray->Address) return nullptr;

	if (InIdx >= InTargetArray->Capacity || InIdx < 0) return nullptr;

	return InTargetArray->Address + (InTargetArray->ElementSize * InIdx);

}

void  array_clear(Array* InTargetArray)
{
	if (!InTargetArray || !InTargetArray->Address) return;

	memset(InTargetArray->Address, 0, (InTargetArray->Capacity * InTargetArray->ElementSize));
}