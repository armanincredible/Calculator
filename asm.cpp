#include "asm.h"
#include "codes_operations.h"
#include "dora.h"
#include "stack.h"

int make_code_rb (Onegin *line, const int amount_operations);

char *copy_in_buffer_from_file_asm (int* amount_operations);


int asmr (void)
{
    int amount_operations = 0;

    char* buffer = copy_in_buffer_from_file_asm (&amount_operations);

    struct Onegin* line = (Onegin*) calloc (amount_operations, sizeof (line));
    if (line == NULL)
    {
        printf ("ERROR in function : %s \n" 
                "haven't memory for struct line\n", __func__);
        return -1;
    }

    make_array_adress (buffer, amount_operations, line);

    make_code_rb (line, amount_operations);

    return 0;
}

char *copy_in_buffer_from_file_asm (int* amount_operations)
{
    char* buffer = NULL;
    
    FILE* asm_file = fopen ("asm.txt", "r");
    if (asm_file != NULL)
    {
        buffer = remove_trash_and_copy_in_buffer (amount_operations, asm_file);
    }
    else 
    {
        printf ("ERROR in function : %s \nasm.txt didn't opened\n", __func__);
        return NULL;
    }

    if (ferror(asm_file))
    {
        printf ("ERROR in function : %s \nreading file falled\n", __func__);
        return NULL;
    }
    fclose (asm_file);

    return buffer;
}


int make_code_rb (Onegin *line, const int amount_operations)
{
    FILE* output_file = fopen ("code.rb", "wb");
    
    if (output_file == NULL)
    {
        printf ("ERROR in function : %s \ncode.rb didn't opened\n", __func__);
        return -1;
    }

    Stack st = {};
    stack_ctor (&st, BASIC_SIZE);

    const char add  [] = "add";
    const char sub  [] = "sub";
    const char mul  [] = "mul";
    const char push [] = "push";
    const char pop  [] = "pop";
    const char div  [] = "div";
    const char out  [] = "out";
    const char hlt  [] = "hlt";

    for (int i = 0; i < amount_operations; i++)
    {
        if (strncmp (push, line[i].adress, 4) == 0)
        {
            elem_t value = 0;

            if (sscanf (line[i].adress + sizeof(push) - 1, "%d", &value) == 0)
            {
                stack_push(&st, -1);
            }
            else
            {
                stack_push(&st, PUSH);
                stack_push(&st, value);
            }

            continue;
        }

        if (strncmp (pop, line[i].adress, 3) == 0)
        {
            stack_push(&st, POP);

            continue;
        }

        if (strncmp (mul, line[i].adress, 3) == 0)
        {
            stack_push(&st, MUL);

            continue;
        }

        if (strncmp (div, line[i].adress, 3) == 0)
        {
            stack_push(&st, DIV);

            continue;
        }

        if (strncmp (add, line[i].adress, 3) == 0)
        {
            stack_push(&st, ADD);

            continue;
        }

        if (strncmp (sub, line[i].adress, 3) == 0)
        {
            stack_push(&st, SUB);

            continue;
        }

        if (strncmp (out, line[i].adress, 3) == 0)
        {
            stack_push(&st, OUT);
            continue;
        }

        if (strncmp (hlt, line[i].adress, 3) == 0)
        {
            stack_push(&st, HLT);
            break;
        }
    }

    fwrite (st.data, sizeof (*st.data), st.size, output_file);

    stack_dtor (&st);

    if (ferror(output_file))
    {
        printf ("ERROR in function : %s \nwriting file falled\n", __func__);
        return -1;
    }
    fclose (output_file);

    return 0;
}