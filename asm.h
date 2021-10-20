#ifndef ASMHEADER
#define ASMHEADER

#include "dora.h"
#include "stack.h"
#include "codes_operations.h"

int make_code_rb (Onegin *line, const int amount_operations);

char *copy_in_buffer_from_file_asm (int* amount_operations);

#endif