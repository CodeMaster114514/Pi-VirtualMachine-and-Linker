#ifndef RUNTIME_HPP
#define RUNTIME_HPP

#include "BasicType.h"
#include "Pi/PMF.h"
#include "heap.hpp"
#include "thread.hpp"

struct Segment
{};

class VM_runtime
{
private:
	VM_heap *heap;
	VM_thread **threads;
	VM_thread *mainThread;
	UINT64 thread_count;
	void copySegment(Pi_segment *segment);
public:
	VM_runtime(VM_heap *heap);
	bool LoadProgram(void *program);
	~VM_runtime();
};

#endif
