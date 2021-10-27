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

    char code_rb [1000] = {0};
    int ip = 0;

    Bit_Type_Comand bit_field = {0};

    #define arg_inm(void)                                       \
            *((Bit_Type_Comand*)(code_rb + ip)) = bit_field;    \
            ip ++;                                              \
                                                                \
            *((int*)(code_rb + ip)) = value;                    \
            ip+=4;                                              \
                                                                \
            printf ("%d\n", ip);                                  \
            continue;

    #define arg_reg(void)                                       \
            *((Bit_Type_Comand*)(code_rb + ip)) = bit_field;    \
            ip ++;                                              \
                                                                \
            *(code_rb + ip) = reg - 'A';                        \
            ip++;                                               \
                                                                            \
            printf ("%d\n", ip);                                  \
            continue;                                           \


    #define arg_reg_inm(void)                                   \
            *((Bit_Type_Comand*)(code_rb + ip)) = bit_field;    \
            ip ++;                                              \
                                                                \
            *(code_rb + ip) = reg - 'A';                        \
            ip++;                                               \
                                                                \
            *((int*)(code_rb + ip)) = value;                    \
            ip+=4;                                              \
                                                                \
            printf ("%d\n", ip);                                 \
            continue;

    #define DEF_CMD(num, name, amount_arg ,...)                                         \
            if (strncmp (#name, line[i].adress, sizeof (#name) - 1) == 0)               \
            {                                                                           \
                bit_field.cmd = num;                                                    \
                                                                                        \
                *((Bit_Type_Comand*)(code_rb + ip)) = bit_field;                        \
                ip ++;                                                                  \
                                                                                        \
                if (num == HLT)                                                         \
                {                                                                       \
                    break;                                                              \
                }                                                                       \
                                                                                        \
                continue;                                                               \
            }

    for (int i = 0; i < amount_operations; i++)
    {
        /*printf ("\n");
        for (int k = 0; (k < ip) && ip > 3; k++)
        {
            printf ("%c", *(code_rb + k) - '0');
        }
        printf ("\n");*/


        bit_field.ram = 0;
        bit_field.reg = 0;
        bit_field.inm = 0;

        elem_t value = 0;
        char reg = 0;

        printf("%s\n", line[i].adress);
        if (sscanf (line[i].adress, "PUSH [%cX + %d]", &reg, &value) == 2)
        {
            printf ("PUSH [%cX + %d]\n", reg, value);
            bit_field.ram = 1;
            bit_field.reg = 1;
            bit_field.inm = 1;
            bit_field.cmd = PUSH;

            arg_reg_inm(void)
        }
        if (sscanf (line[i].adress, "PUSH [%d]", &value) == 1)
        {
            printf ("PUSH [%d]\n", value);
            bit_field.ram = 1;
            bit_field.reg = 0;
            bit_field.inm = 1;
            bit_field.cmd = PUSH;

            arg_inm(void)
        }
        if (sscanf (line[i].adress, "PUSH [%cX]", &reg) == 1)
        {
            printf ("PUSH [%cX]\n", reg);
            bit_field.ram = 1;
            bit_field.reg = 1;
            bit_field.inm = 0;
            bit_field.cmd = PUSH;

            arg_reg(void)
        }

        if (sscanf (line[i].adress, "PUSH %cX + %d", &reg, &value) == 2)
        {
            printf ("PUSH %cX + %d\n", reg, value);
            bit_field.ram = 0;
            bit_field.reg = 1;
            bit_field.inm = 1;
            bit_field.cmd = PUSH;

            arg_reg_inm(void)
        }

        if (sscanf (line[i].adress, "PUSH %d", &value) == 1)
        {
            printf ("PUSH %d\n", value);
            bit_field.ram = 0;
            bit_field.reg = 0;
            bit_field.inm = 1;
            bit_field.cmd = PUSH;

            arg_inm(void)
        }

        if (sscanf (line[i].adress, "PUSH %cX", &reg) == 1)
        {
            printf ("PUSH %cX\n", reg);
            bit_field.ram = 0;
            bit_field.reg = 1;
            bit_field.inm = 0;
            bit_field.cmd = PUSH;

            arg_reg(void)
        }

        if (sscanf (line[i].adress, "POP [%cX + %d]", &reg, &value) == 2)
        {
            printf ("POP [%cX + %d]\n", reg, value);
            bit_field.ram = 1;
            bit_field.reg = 1;
            bit_field.inm = 1;
            bit_field.cmd = POP;

            arg_reg_inm(void)
        }

        if (sscanf (line[i].adress, "POP [%d]", &value) == 1)
        {
            printf ("POP [%d]\n", value);
            bit_field.ram = 1;
            bit_field.reg = 0;
            bit_field.inm = 1;
            bit_field.cmd = POP;

            arg_inm(void)
        }

        if (sscanf (line[i].adress, "POP [%cX]", &reg) == 1)
        {
            printf ("POP [%cX]\n", reg);
            bit_field.ram = 1;
            bit_field.reg = 1;
            bit_field.inm = 0;
            bit_field.cmd = POP;

            arg_reg(void)
        }

        if (sscanf (line[i].adress, "POP %cX", &reg) == 1)
        {
            printf ("POP %cX\n", reg);
            bit_field.ram = 0;
            bit_field.reg = 1;
            bit_field.inm = 0;
            bit_field.cmd = POP;

            arg_reg(void)
        }

        #include "commands.def"
    }


    #undef DEF_CMD

    #undef arg_inm

    #undef arg_reg

    #undef arg_reg_inm

    fwrite (code_rb, sizeof (char), ip, output_file);

    if (ferror(output_file))
    {
        printf ("ERROR in function : %s \n"
                "writing file falled\n", __func__);
        return -1;
    }
    fclose (output_file);

    return 0;
}