#include "grid.h"
#include <stdlib.h>
#include <assert.h>

GRID init_grid(int size_grid) {
    GRID g;
    if(size_grid > 0 && (size_grid%2 == 0)) {
        g.size_grid = size_grid;
    } else {
        printf("size_grid uncorrect, we choose default value\n");
        g.size_grid = 8;
    }
    g.board = (int **)calloc(g.size_grid, sizeof(int *));
    assert(g.board != NULL);
    for(int i = 0; i < g.size_grid; i++) {
        g.board[i] = (int *)calloc(g.size_grid, sizeof(int));
        assert(g.board[i] != NULL);
    }
    g.nb_white = 0;
    g.nb_black = 0;

    int middle = (int) g.size_grid/2;
    g.board[middle-1][middle-1] = 'W';
    g.board[middle][middle] = 'W';
    g.board[middle-1][middle] = 'B';
    g.board[middle][middle-1] = 'B';
    g = pointCounter(g);
    return g;
}

GRID pointCounter (GRID g) {
    g.nb_white = 0;
    g.nb_black = 0;
    for(int i = 0; i < g.size_grid; i++) {
        for(int j = 0; j < g.size_grid; j++) {
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
                    printf("|  ", g.board[i][j]);
                }
        }
        printf("|\n");
    }
    printf("-----------------------");
}
