#ifndef RUNTIME_HPP
#define RUNTIME_HPP

extern "C"
{
	#include "BasicType.h"
	#include "Pi/PMF.h"
}
#include "heap.hpp"
#include "thread.hpp"

struct Segment
{
	UINT64 size;
	UINT8 type;
	UINT8 flag;
	UINT32 seg_id;
	UINT8 *data;
};

class VM_runtime
{
private:
	VM_heap *heap;
	VM_thread **threads;
	VM_thread *mainThread;
	Segment **segments;
	Pi_symbol *symbols;
	UINT64 symbol_count;
	UINT32 segment_count;
	UINT64 thread_count;
	bool LoadSegment(Pi_program_header *program_head, void *file_start);
	bool LoadSymbol(Pi_symbol_header *symbol_head);
	void copySegment(Pi_segment *segment, void *file_start);

public:
	VM_runtime(VM_heap *heap);
	bool LoadProgram(void *program);
	~VM_runtime();
};

#endif
