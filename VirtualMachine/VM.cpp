#include "VM.hpp"
#include "heap.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ranges>

VM::VM(UINT64 MaxHeapSize)
{
	this->heap = new VM_heap(MaxHeapSize);
	this->runtime = new VM_runtime(this->heap);
}

static void *copy_file(FILE *file)
{
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	void *target = malloc(size);
	fseek(file, 0, SEEK_SET);

	char *target_write = (char *)target;
	for (size_t i = 0; i < size; ++i)
	{
		target_write[i] = getc(file);
	}
	return target;
}

VM_return_value VM::ready_running_file(const char *file)
{
	VM_return_value return_value = VM_process_success;

	FILE *PMF = fopen(file, "r");
	if (!PMF)
	{
		return VM_process_could_not_open_file;
	}

	if(!this->runtime->LoadProgram(copy_file(PMF)))
	{
		return VM_process_failed;
	}

	return return_value;
}

int VM::run()
{
	return 0;
}

VM::~VM()
{
	delete this->heap;
	delete this->runtime;
}
