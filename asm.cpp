#include "asm.h"

char *copy_in_buffer_from_file_asm (int* amount_operations)
{
    char* buffer = NULL; 
    ///////////ASSERT AMOUNT_OPERATONS
    FILE* asm_file = fopen ("asm.txt", "r");
    if (asm_file != NULL)
    {
        buffer = remove_trash_and_copy_in_buffer (amount_operations, asm_file);
    }
    else 
    {
        printf ("ERROR in function : %s \n"
                "asm.txt didn't opened\n", __func__);
        return NULL;
    }

    if (ferror(asm_file))
    {
        printf ("ERROR in function : %s \n"
                "reading file falled\n", __func__);
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
        printf ("ERROR in function : %s \n"
                "code.rb didn't opened\n", __func__);
        return -1;
    }

    Stack st = {};
    stack_ctor (&st, BASIC_SIZE);

    #define DEF_CMD(num, name, amount_arg ,...)                               \
            if (strncmp (#name, line[i].adress, sizeof (#name) - 1) == 0)     \
            {                                                                 \
                stack_push (&st, num);                                        \
                if (amount_arg > 0)                                           \
                {                                                             \
                    elem_t value = 0;                                         \
                    sscanf (line[i].adress + 4, "%d", &value);                \
                    stack_push(&st, value);                                   \
                }                                                             \
                if (num == HLT)                                               \
                {                                                             \
                    break;                                                    \
                }                                                             \
                continue;                                                     \
            }

    for (int i = 0; i < amount_operations; i++)
    {
        #include "commands.def"
    }

    #undef DEF_CMD

    fwrite (st.data, sizeof (*st.data), st.size, output_file);

    stack_dtor (&st);

    if (ferror(output_file))
    {
        printf ("ERROR in function : %s \n"
                "writing file falled\n", __func__);
        return -1;
    }
    fclose (output_file);

    return 0;
}