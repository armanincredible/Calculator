#include "calc.h"

int main ()
{
    if (cmp_files() == 1)
    {
        asmr();
    }

    proc();

    make_disasm();

    return 0;
}
