#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <libintl.h>
#include <stdlib.h>

#include "BasicType.h"
#include "heap.hpp"
#include "runtime.hpp"
#include "stack.hpp"

#define _(string) gettext(string)
#define LOCALEDIR "/usr/share/locale"
#define PACKAGE "pi"

enum VM_return_value
{
	VM_process_success,
	VM_process_failed,
	VM_process_could_not_open_file
};

class VM
{
private:
	VM_heap *heap;
	VM_runtime *runtime;

public:
	VM(UINT64 MaxHeapSize);
	~VM();
	VM_return_value ready_running_file(const char *file);
};

#endif
