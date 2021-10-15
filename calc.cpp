#include "calc.h"
#include "codes_operations.h"
#include "sys\stat.h"

int cmp_files (void)
{
    struct stat status_asm; 
    stat ("asm.txt", &status_asm);

    struct stat status_code; 
    stat ("code.rb", &status_code);

    if ((status_code.st_size == 0) ||
        (status_asm.st_mtime > status_code.st_mtime))
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int proc (void)
{
    Stack st = {};
    stack_ctor (&st, BASIC_SIZE);

    calculate (&st);

    stack_dump (&st, __FILE__, __func__, __LINE__);

    stack_dtor (&st);

    return 0;
}

elem_t calculate (Stack* stack)
{
    FILE* input_file = fopen ("code.rb", "rb");
    if (input_file == NULL)
    {
        printf ("ERROR in function : %s \ncode.rb didn't open\n", __func__);
        return -1;
    }

    FILE* calc_dump = fopen ("calcstatus.txt", "w");
    if (calc_dump == NULL)
    {
        printf ("ERROR in function : %s \ncalcstatus.txt didn't open\n", __func__);
        return -1;
    }

    elem_t* array = make_array (input_file);

    int amount = 0;
    int operation = 0;

    while (1)
    {   
        operation = array [amount];

        if (operation == PUSH)
        {
            fprintf (calc_dump, "%d : %d\n", operation, array[amount + 1]);
        }
        else 
        {
            fprintf (calc_dump, "%d\n", operation);
        }

        switch (operation)
        {
            case ERROR:
            {
                return 0;
                break;
            }
            case PUSH: 
            {
                int value = array [amount + 1];
                amount += 2;

                stack_push (stack, value);

                break;
            }
            case POP:
            {
                elem_t variable = 0;
                stack_pop (stack, &variable);

                amount++;
                break;
            }
            case MUL:
            {
                elem_t fr_var = 0;
                elem_t sec_var = 0;
                stack_pop (stack, &fr_var);
                stack_pop (stack, &sec_var);

                stack_push (stack, fr_var * sec_var);

                amount++;
                break;
            }
            case DIV:
            {
                elem_t fr_var = 0;
                elem_t sec_var = 0;
                stack_pop (stack, &fr_var);
                stack_pop (stack, &sec_var);

                stack_push (stack, fr_var / sec_var); 

                amount++;
                break;
            }
            case ADD:
            {
                elem_t fr_var = 0;
                elem_t sec_var = 0;
                stack_pop (stack, &fr_var);
                stack_pop (stack, &sec_var);

                stack_push (stack, fr_var + sec_var);

                amount++;
                break;
            }
            case SUB:
            {
                elem_t fr_var = 0;
                elem_t sec_var = 0;
                stack_pop (stack, &fr_var);
                stack_pop (stack, &sec_var);

                stack_push (stack, fr_var + sec_var);
                
                amount++;
                break;
            }
            case OUT:
            {
                printf ("%d\n", stack_top (stack));
                amount++;
                break;
            }
            case HLT:
            {
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
    fclose (input_file);

    if (ferror(calc_dump))
    {
        printf ("ERROR in function : %s \nwriting calc_dump falled\n", __func__);
        return -1;
    }
    fclose (calc_dump);

    return 0;
}