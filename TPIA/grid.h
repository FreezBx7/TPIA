#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

typedef struct {
    int size_grid;
    int nb_white;
    int nb_black;
    char** board;
} GRID;

GRID init_grid(int size_grid);

GRID pointCounter (GRID g);

void print_GRID(GRID g);


#endif // GRID_H_INCLUDED
