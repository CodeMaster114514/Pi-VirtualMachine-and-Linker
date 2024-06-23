#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "BasicType.h"

typedef void * Pi_VM_address;

class Block;

class VM_heap
{
private:
	Block **blocks;
	UINT64 MaxHeapSize;
	UINT32 block_count;
public:
	VM_heap(UINT64 MaxHeapSize);
	~VM_heap();
	Pi_VM_address MallocMemory(UINT64 size);
	Pi_VM_address CallocMemory(UINT64 count, UINT64 size);
	Pi_VM_address ReallocMemory(Pi_VM_address address, UINT64 size);
	void FreeMemory(Pi_VM_address address);
	void GC();
};

class Block
{
private:
	void *memory;
	UINT64 size;
	UINT64 counter;
public:
	Block(UINT64 size);
	bool CheckBlock();
	void *getMemoryAddress();
	void resetMemorySize(UINT64 size);
	~Block();
};

#endif
