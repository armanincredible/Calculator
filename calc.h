#ifndef CALCHEADER
#define CALCHEADER

#include "stack.h"
#include "dora.h"
#include "sys\stat.h"
#include "codes_operations.h"

const int amount_regs = 4;

elem_t calculate (Stack* stack, elem_t* Regs);

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