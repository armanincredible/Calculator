#include "calc.h"

int calculate (Stack* stack, Onegin *line, const int amount_operations)
{
    char add  [] = "add";
    char sub  [] = "sub";
    char mul  [] = "mul";
    char push [] = "push";
    char pop  [] = "pop";
    char div  [] = "div";
    char out  [] = "out";
    char hlt  [] = "hlt";

    /*for (int ind = 0; ind < amount_operations - 1; ind++)
    {
        puts (line[ind].adress);
    }*/

    for (int i = 0; i < amount_operations; i++)
    {
        if (strncmp (push, line[i].adress, 4) == 0)
        {
            int value = 0;
            sscanf (line[i].adress + 4, "%d", &value);
            stack_push (stack, value);

            continue;
        }

        if (strncmp (pop, line[i].adress, 3) == 0)
        {
            elem_t variable = 0;
            stack_pop (stack, &variable);

            continue;
        }

        if (strncmp (mul, line[i].adress, 3) == 0)
        {
            elem_t fr_var;
            elem_t sec_var;
            stack_pop (stack, &fr_var);
            stack_pop (stack, &sec_var);

            stack_push (stack, fr_var * sec_var);

            continue;
        }

        if (strncmp (div, line[i].adress, 3) == 0)
        {
            elem_t fr_var;
            elem_t sec_var;
            stack_pop (stack, &fr_var);
            stack_pop (stack, &sec_var);

            stack_push (stack, fr_var / sec_var); 

            continue;
        }

        if (strncmp (add, line[i].adress, 3) == 0)
        {
            elem_t fr_var;
            elem_t sec_var;
            stack_pop (stack, &fr_var);
            stack_pop (stack, &sec_var);

            stack_push (stack, fr_var + sec_var);

            continue;
        }

        if (strncmp (sub, line[i].adress, 3) == 0)
        {
            elem_t fr_var;
            elem_t sec_var;
            stack_pop (stack, &fr_var);
            stack_pop (stack, &sec_var);

            stack_push (stack, fabs (fr_var - sec_var));

            continue;
        }

        if (strncmp (out, line[i].adress, 3) == 0)
        {
            printf ("%d", stack_top (stack));
            continue;
        }

        if (strncmp (hlt, line[i].adress, 3) == 0)
        {
            break;
        }
    }

    return 0;
}
