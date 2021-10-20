#include "calc.h"

elem_t calculate (Stack* stack)
{
    if (stack == NULL)
    {
        printf ("ERROR in function : %s \n"
                "stack have zero adress\n", __func__);
        return -1;
    }

    FILE* input_file = fopen ("code.rb", "rb");
    if (input_file == NULL)
    {
        printf ("ERROR in function : %s \n"
                "code.rb didn't open\n", __func__);
        return -1;
    }

    FILE* calc_dump = fopen ("calcstatus.txt", "w");
    if (calc_dump == NULL)
    {
        printf ("ERROR in function : %s \n"
                "calcstatus.txt didn't open\n", __func__);
        return -1;
    }

    elem_t* array = make_array (input_file);
    if (array == NULL)
    {
        printf ("ERROR in function : %s \n"
                "array have zero adress\n", __func__);
        return -1;
    }

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

        #define DEF_CMD(num, name, hz , arg)    \
                case name:                      \
                {                               \
                    arg                         \
                    break;                      \
                }                               

        switch (operation)
        {
            #include "commands.def"
        }
        
        #undef DEF_CMD

        if (operation == HLT)
        {
            break;
        }
    }
    
    if (ferror(input_file))
    {
        printf ("ERROR in function : %s \n"
                "reading input_file falled\n", __func__);
        return -1;
    }
    fclose (input_file);

    if (ferror(calc_dump))
    {
        printf ("ERROR in function : %s \n"
                "writing calc_dump falled\n", __func__);
        return -1;
    }
    fclose (calc_dump);

    return 0;
}

elem_t* make_array (FILE* input_file)
{
    if (input_file == NULL)
    {
        printf ("ERROR in function : %s \n"
                "input_file have NULL adress\n", __func__);
        return NULL;
    }

    int size = size_file (input_file);////////////////////////////////SIZE_TTTTTTTTTT

    elem_t* array = (elem_t*) calloc (size, sizeof(int));
    if (array == NULL)
    {
        printf ("ERROR in function : %s \n"
                "haven't memory for array\n", __func__);
        return NULL;
    }

    fread (array, sizeof (char), size, input_file); /////////////obrabotka

    return array;
}
