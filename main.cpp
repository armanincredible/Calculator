#include "calc.h"

int main ()
{
    int amount_operations = 0;

    char* buffer = remove_trash_and_copy_in_buffer (&amount_operations);

    struct Onegin* line = (Onegin*) calloc (amount_operations, sizeof (line));
    if (line == NULL)
    {
        printf ("ERROR in function : %s \n" 
                "haven't memory for struct line\n", __func__);
        return -1;
    }

    make_array_adress (buffer, amount_operations, line);

    Stack st = {};
    stack_ctor (&st, BASIC_SIZE);

    calculate (&st, line, amount_operations);

    stack_dump (&st, __FILE__, __func__, __LINE__);

    stack_dtor (&st);
}
