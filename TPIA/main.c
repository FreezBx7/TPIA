#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main()
{
    printf("TP Intelligence Artificielle\n");
    GRID g = init_grid(6);
    GRID gPossibility = init_grid(6);
    //gPossibility = copieGRID(g);
    print_GRID(g);
    gPossibility = whereCanIPlay(g,'B');
    printf("--------- Possibility Grid ---------\n");
    print_GRID(gPossibility);
    play(g,gPossibility,'B');
    print_GRID(g);






    return 0;
}
