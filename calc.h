#ifndef CALCHEADER
#define CALCHEADER

#include "stack.h"
#include "dora.h"
#include "sys\stat.h"
#include "codes_operations.h"

elem_t calculate (Stack* stack);

int proc (void);

elem_t* make_array (FILE* input_file);

struct Calc
{
    struct Stack st;
    char* ds;
    elem_t* Regs;
    int* code;
};

#endif