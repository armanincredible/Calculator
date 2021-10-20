#include "asm.h"

int main (void) //rename asmr
{
    int amount_operations = 0; //n_operations size_t

    char* buffer = copy_in_buffer_from_file_asm (&amount_operations); //laconichnee

    Onegin* line = (Onegin*) calloc (amount_operations, sizeof (Onegin));
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
