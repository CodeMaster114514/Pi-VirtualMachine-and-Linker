#include <stdlib.h>
#include <ranges>

#include "runtime.hpp"
#include "BasicType.h"
#include "Pi/PMF.h"
#include "heap.hpp"

VM_runtime::VM_runtime(VM_heap *heap)
{
	this->heap = heap;
}

void VM_runtime::copySegment(Pi_segment *segment, void *file_start)
{
	if (!this->segments)
	{
		this->segments = (Segment **)malloc(sizeof(Segment *));
		this->segment_count = 1;
	}
	{
		this->segments = (Segment **)realloc(this->segments, sizeof(Segment *) * ++this->segment_count);
	}
	this->segments[this->segment_count - 1] = (Segment *)malloc(sizeof(Segment));
	Segment *target = this->segments[this->segment_count - 1];
	target->data = (UINT8 *)(segment->file_offset + (UINT64)file_start);
	target->type = segment->segment_type;
	target->flag = segment->segment_flag;
	target->size = segment->size;
	target->seg_id = segment->segment_id;
}

bool VM_runtime::LoadSegment(Pi_program_header *program_head, void *file_start)
{
	Pi_segment *segments = program_head->segments_enter;
	for (UINT64 i = 0; i < program_head->segment_count; ++i)
	{
		if (segments[i].segment_type == PI_SEGMENT_LOAD)
		{
			this->copySegment(&segments[i], file_start);
		}
	}
	return true;
}

bool VM_runtime::LoadSymbol(Pi_symbol_header *symbol_head)
{
	this->symbols = symbol_head->symbols_enter;
	this->symbol_count = symbol_head->symbol_count;
	return true;
}

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
	this->LoadSegment((Pi_program_header *)module_head->program_header_offset + (UINT64)program, program);
	this->LoadSymbol((Pi_symbol_header *)module_head->symbol_header_offset + (UINT64)program);
	return true;
}

VM_runtime::~VM_runtime()
{
	for (UINT64 i = 0; i < this->thread_count; ++i)
	{
		delete this->threads[i];
	}
	if (this->segments)
	{
		for (UINT64 i = 0; i < this->segment_count; ++i)
		{
			free(this->segments[i]);
		}
		free(this->segments);
	}
}
