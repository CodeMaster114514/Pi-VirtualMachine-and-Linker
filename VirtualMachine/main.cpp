#include "VM.hpp"
#include <libintl.h>

extern const char *NotAnyArgs;

int main(int argc, char *args[])
{
	if (argc == 1)
	{
		printf(_(NotAnyArgs));
	}
	VM *vm = new VM(4096*1024);
	delete vm;
}
