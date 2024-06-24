#include "VM.hpp"
#include <libintl.h>

extern const char *NotAnyArgs;
extern const char *CouldNotOpen;
extern const char *LoadFailed;

using namespace std;

int main(int argc, char *args[])
{
	int ret = -1;
	if (argc == 1)
	{
		cout << _(NotAnyArgs);
		return ret;
	}
	VM *vm = new VM(4096*1024);
	
	if (vm->ready_running_file(args[1]) == VM_process_could_not_open_file)
	{
		cout << _(CouldNotOpen);
	}
	ret = vm->run();
	delete vm;
	return ret;
}
