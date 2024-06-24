#ifndef RUN_H
#define RUN_H

#include "BasicType.h"
#include <stdbool.h>

enum
{
	PI_MODULE_FILE_FLAG_LITTLE_ENDIAN = 0b00000000,
	PI_MODULE_FILE_FLAG_BIG_ENDIAN = 0b00000001
};

enum
{
	PI_SEGMENT_LOAD,
	PI_SEGMENT_OS,
	PI_SEHMENT_NOTE
};

enum
{
	Pi_SEGMENT_FLAG_EXECUTABLE = 0b00000001,
	Pi_SEGMENT_FLAG_READONLY = 0b00000010
};

typedef struct
{
	char magic_number[3];
	bool isExecutable;
	UINT8 verson;
	UINT8 file_flag;
	UINT64 file_size;
	UINT64 program_header_offset;
	UINT64 symbol_header_offset;
} Pi_module_header;

typedef struct
{
	UINT8 segment_type;
	UINT8 segment_flag;
	UINT32 segment_id;
	UINT64 size;
	UINT64 file_offset;
} Pi_segment;

typedef struct
{
	UINT64 segment_count;
	Pi_segment segments_enter[];
} Pi_program_header;

typedef struct
{
	UINT8 symbol_type;
	UINT8 symbol_len;
	UINT32 symbol_id;
	UINT32 symbol_at_segment_id;
	UINT64 offset_in_segment;
	char name[];
} Pi_symbol;

typedef struct
{
	UINT64 symbol_count;
	Pi_symbol symbols_enter[];
} Pi_symbol_header;

// about PMF.c
bool isPiModuleFile(Pi_module_header *header);
bool isExecutableFile(Pi_module_header *header);

#endif
