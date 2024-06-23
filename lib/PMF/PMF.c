/* This file is defined the functions of Pi module file.
 * 这个文件定义了一下关于Pi module file和一些函数 */

#include "Pi/PMF.h"
#include <stdbool.h>
#include <string.h>

bool isPiModuleFile(Pi_module_header *header)
{
	return (strcmp("PMF", header->magic_number) == 0);
}

bool isExecutableFile(Pi_module_header *header)
{
	return header->isExecutable;
}
