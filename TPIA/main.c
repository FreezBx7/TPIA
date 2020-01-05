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

    for(int v = 0; v < 7; v++) {
        for(int u = 0; u <  5; u++) {
            printf("%d;%d\n", v,u);
            if(u == 2) {

                break;
            }
        }
    }






    return 0;
}
