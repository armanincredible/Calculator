#ifndef CODEOPERATIONS
#define CODEOPERATIONS

#define DEF_CMD(num, name, ...) \
        name = num,

enum commands
{
    #include "commands.def"
};

#undef DEF_CMD

#endif


/*enum operations
{
    ERROR = -1,
    HLT,
    PUSH,
    POP,
    ADD,
    SUB,
    MUL,
    DIV,
    OUT
};*/