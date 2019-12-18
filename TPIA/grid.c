#include "grid.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

GRID init_grid(int size_grid) {
    GRID g;
    if(size_grid > 0 && (size_grid%2 == 0)) {
        g.size_grid = size_grid;
    } else {
        printf("size_grid uncorrect, we choose default value\n");
        g.size_grid = 8;
    }
    g.board = (char **)calloc(g.size_grid + 2, sizeof(char *));
    assert(g.board != NULL);
    for(int i = 0; i < g.size_grid; i++) {
        g.board[i] = (char *)calloc(g.size_grid +2, sizeof(char));
        assert(g.board[i] != NULL);
    }
    g.nb_white = 0;
    g.nb_black = 0;

    int middle = (int) g.size_grid/2;
    g.board[middle][middle] = 'W';
    g.board[middle+1][middle+1] = 'W';
    g.board[middle][middle+1] = 'B';
    g.board[middle+1][middle] = 'B';

    for(int k = 0; k<g.size_grid+2; k++) {
        g.board[0][k] = 'N';
        g.board[k][0] = 'N';
        g.board[g.size_grid + 2][k] = 'N';
        g.board[k][g.size_grid + 2] = 'N';
    }


    g = pointCounter(g);
    return g;
}

GRID pointCounter (GRID g) {
    g.nb_white = 0;
    g.nb_black = 0;
    for(int i = 1; i < g.size_grid + 1; i++) {
        for(int j = 1; j < g.size_grid + 1; j++) {
            if(g.board[i][j] == 'B') {
                g.nb_black++;
            } else {
                if(g.board[i][j] == 'W') {
                    g.nb_white++;
                }
            }
        }
    }
    return g;
}

void print_GRID(GRID g) {
    for(int i = 0; i<g.size_grid; i++) {
        for(int j = 0; j<g.size_grid; j++) {
                if(g.board[i][j]) {
                    printf("|%c ", g.board[i][j]);
                } else {
                    printf("|  ");
                }
        }
        printf("|\n");
    }
    printf("-----------------------");
}

/*void whereCanIPlay(GRID g, char myColor) {
    //char adversaryColor;
    if( myColor == 'W') {
        adversaryColor = 'B';
    } else {
        adversaryColor = 'W';
    }

    for(int i = 0; i<g.size_grid; i++) {
        for(int j = 0; j<g.size_grid; j++) {
            //isAadversaryNeigbour(g, i, j);
        }
    }
}*/
/*
bool isAadversaryNeigbour(GRID g, int i, int j) {
    int ** result;

    result = (int **)calloc(g.size_grid, sizeof(int *));
    assert(result!= NULL);
    for(int i = 0; i < g.size_grid; i++) {
        result[i] = (int *)calloc(g.size_grid, sizeof(int));
        assert(result[i] != NULL);
    }
    if(i == 0) {
    // Can't do board[i-1]
        if(j == 0) {
        //Can't do board[][j-1]
            if((g.board[i][j+1] || g.board [i+1][j] || g.board[i+1][j+1]) == adversatyColor) {
                return true;
            }

            if()


            } else {
                if(j == g.size_grid) {
                    //Can't do board[][j+1]
                } else {
                    if (j > 0 && j < g.size_grid){

                    } else {
                        return false;
                    }
                }
            }

    } else {

            if(i == g.size_grid) {

                if(j == 0) {

                } else {
                    if(j == g.size_grid) {

                    } else {
                        if (j > 0 && j < g.size_grid){

                        } else {
                            return false;
                        }
                    }
                }
            } else {
                if(i < g.size_grid && i > 0) {
                    if(j == 0) {

            } else {
                if(j == g.size_grid) {

                    } else {
                        if (j > 0 && j < g.size_grid){

                        } else {
                            return false;
                        }
                    }
                }
                } else {
                    return false;
                }
            }

    }
}
*/
