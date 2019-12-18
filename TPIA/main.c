#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main()
{
    printf("Hello world!\n");
    GRID g = init_grid(6);
    print_GRID(g);
    whereCanIPlay(g,'B');



    return 0;
}
