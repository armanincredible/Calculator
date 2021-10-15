#include "dora.h"
#include "stack.h"
#include "codes_operations.h"

elem_t* make_array (FILE* input_file);

int make_disasm (void)
{
    FILE* output_file = fopen ("disasm.txt", "w");
    if (output_file == NULL)
    {
        printf ("ERROR in function : %s \ndisasm.txt didn't open\n", __func__);
        return -1;
    }

    FILE* input_file = fopen ("code.rb", "rb");
    if (input_file == NULL)
    {
        printf ("ERROR in function : %s \ncode.rb didn't open\n", __func__);
        return -1;
    }

    elem_t* array = make_array (input_file);

    int amount = 0;
    int operation = 0;

    while (1)
    {   
        operation = array [amount];

        switch (operation)
        {
            case ERROR:
            {
                fprintf (output_file, "ERROR\n");
                amount++;
                break;
            }
            case PUSH: 
            {
                int value = array [amount + 1];
                amount += 2;
                fprintf (output_file, "PUSH %d\n", value);
                break;
            }
            case POP:
            {
                fprintf (output_file, "POP\n");
                amount++;
                break;
            }
            case MUL:
            {
                fprintf (output_file, "MUL\n");
                amount++;
                break;
            }
            case DIV:
            {
                fprintf (output_file, "DIV\n");
                amount++;
                break;
            }
            case ADD:
            {
                fprintf (output_file, "ADD\n");
                amount++;
                break;
            }
            case SUB:
            {
                fprintf (output_file, "SUB\n");
                amount++;
                break;
            }
            case OUT:
            {
                fprintf (output_file, "OUT\n");
                amount++;
                break;
            }
            case HLT:
            {
                fprintf (output_file, "HLT");
                break;
            }
            default:
            {
                break;
            }
        }

        if (operation == HLT)
        {
            break;
        }
    }

    if (ferror(input_file))
    {
        printf ("ERROR in function : %s \nreading input_file falled\n", __func__);
        return -1;
    }
    
    if (ferror(output_file))
    {
        printf ("ERROR in function : %s \nwriting output_file falled\n", __func__);
        return -1;
    }

    fclose (output_file);
    fclose (input_file);

    return 0;
}

elem_t* make_array (FILE* input_file)
{
    if (input_file == NULL)
    {
        printf ("ERROR in function : %s \ninput_file have NULL adress\n", __func__);
        return NULL;
    }

    int size = size_file (input_file);

    elem_t* array = (elem_t*) calloc (size, sizeof(int));
    if (array == NULL)
    {
        printf ("ERROR in function : %s \nhaven't memory for array\n", __func__);
        return NULL;
    }

    fread (array, sizeof (char), size, input_file);

    return array;
}