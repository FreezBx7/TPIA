#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#define EAST 1
#define WEST 2
#define SOUTH 3
#define NORTH 4
#define NE 5
#define NW 6
#define SE 7
#define SW 8

typedef int DIRECTION;

typedef struct {
    int size_grid;
    int nb_white;
    int nb_black;
    char** board;
} GRID;

GRID init_grid(int size_grid);

GRID pointCounter (GRID g);

void print_GRID(GRID g);

void isNeigbourAdversary(GRID g, int xPos, int yPos, char myColor);

DIRECTION defineDIRECTION(int xPos, int yPos, int i, int j);

GRID whereCanIPlay(GRID g, char myColor);

void canIPlay(GRID g, DIRECTION dir, int xPos, int yPos, char myColor);

/* Dev purposes do not use*/
GRID insertIntoGRID(GRID g,int xPos,int yPos,char myColor);


#endif // GRID_H_INCLUDED
