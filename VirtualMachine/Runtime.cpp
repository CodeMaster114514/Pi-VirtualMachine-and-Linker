#include "runtime.hpp"
#include "BasicType.h"
#include "Pi/PMF.h"
#include "heap.hpp"

VM_runtime::VM_runtime(VM_heap *heap)
{
	this->heap = heap;
}

void VM_runtime::copySegment

bool VM_runtime::LoadProgram(void *program)
{
	Pi_module_header *module_head = (Pi_module_header *)program;
	if (!isPiModuleFile(module_head))
	{
		return false;
	}
	if (!isExecutableFile(module_head))
	{
		return false;
	}
	Pi_program_header *program_head = (Pi_program_header *)((UINT64)program + module_head->program_header_offset);
	Pi_segment *segments = program_head->segments_enter;
	for (UINT64 i = 0; i < program_head->segment_count; ++i)
	{
		if (segments[i].segment_type == PI_SEGMENT_LOAD) {
			this->copySegment(&segments[i]);
		}
	}
}

VM_runtime::~VM_runtime()
{
	for (UINT64 i = 0; i < this->thread_count; ++i)
	{
		delete this->threads[i];
	}
}
