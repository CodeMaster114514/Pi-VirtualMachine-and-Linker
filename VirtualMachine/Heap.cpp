#include "heap.hpp"
#include "BasicType.h"
#include <cstdlib>
#include <stdlib.h>

VM_heap::VM_heap(UINT64 MaxHeapSize)
{
	this->MaxHeapSize = MaxHeapSize;
}

VM_heap::~VM_heap()
{
	for (UINT64 i = 0; i < this->block_count; ++i)
	{
		delete this->blocks[i];
	}
	free(this->blocks);
}

Pi_VM_address VM_heap::MallocMemory(UINT64 size)
{
	UINT64 Block_p_Size = sizeof(void *);
	this->blocks = (Block **) realloc(this->blocks, ++this->block_count * Block_p_Size);
	this->blocks[this->block_count - 1] = new Block(size);
	return this->blocks[this->block_count - 1]->getMemoryAddress();
}

Pi_VM_address VM_heap::CallocMemory(UINT64 count, UINT64 size)
{
	UINT64 Block_p_Size = sizeof(void *);
	this->blocks = (Block **) realloc(this->blocks, ++this->block_count * Block_p_Size);
	this->blocks[this->block_count - 1] = new Block(count * size);
	return this->blocks[this->block_count - 1]->getMemoryAddress();
}

Pi_VM_address VM_heap::ReallocMemory(Pi_VM_address address, UINT64 size)
{
	Block *target = NULL;
	for (UINT64 i; i < this->block_count; ++i)
	{
		if (this->blocks[i]->getMemoryAddress() == address)
		{
			target = this->blocks[i];
			target->resetMemorySize(size);
			goto finish;
		}
	}
finish:
	return target->getMemoryAddress();
}

void VM_heap::FreeMemory(Pi_VM_address address)
{
	bool isFinded = false;
	for (UINT64 i; i < this->block_count; ++i)
	{
		if (!isFinded && this->blocks[i]->getMemoryAddress() == address)
		{
			delete this->blocks[i];
			isFinded = true;
			continue;
		}
		if (isFinded) {
			this->blocks[i - 1] = this->blocks[i];
		}
	}
}

void VM_heap::GC()
{
	for (UINT64 i = 0; i < this->block_count; ++i)
	{
		if (this->blocks[i]->CheckBlock())
		{
			for (UINT64 j = i + 1; j < this->block_count; ++j)
			{
				this->blocks[i] = this->blocks[j];
			}
		}
	}
}

Block::Block(UINT64 size)
{
	this->memory = malloc(size);
	this->size = size;
	this->counter = 1;
}

Block::~Block()
{
	free(this->memory);
}

Pi_VM_address Block::getMemoryAddress()
{
	return this->memory;
}

bool Block::CheckBlock()
{
	if (this->counter <= 0)
	{
		delete this;
		return true;
	}
	return false;
}

void Block::resetMemorySize(UINT64 size)
{
	this->memory = realloc(this->memory, size);
	this->size = size;
}
