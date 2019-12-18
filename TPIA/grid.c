#include "grid.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


GRID reservationMemoire(int size_grid) {
     GRID g;
     if(size_grid > 0 && (size_grid%2 == 0)) {
        g.size_grid = size_grid + 2;
    } else {
        printf("size_grid uncorrect, we choose default value\n");
        g.size_grid = 10;
    }
    g.board = (char **)calloc(g.size_grid, sizeof(char *));
    assert(g.board != NULL);
    for(int i = 0; i < g.size_grid; i++) {
        g.board[i] = (char *)calloc(g.size_grid, sizeof(char));
        assert(g.board[i] != NULL);
    }
    return g;
}

GRID init_grid(int size_grid) {
    GRID g = reservationMemoire(size_grid);

    g.nb_white = 0;
    g.nb_black = 0;

    int middle = (int) (g.size_grid/2)-1;
    g.board[middle][middle] = 'W';
    g.board[middle+1][middle+1] = 'W';
    g.board[middle][middle+1] = 'B';
    g.board[middle+1][middle] = 'B';


    for(int k = 0; k<g.size_grid; k++) {
        g.board[0][k] = 'N';
        g.board[k][0] = 'N';
        g.board[g.size_grid-1][k] = 'N';
        g.board[k][g.size_grid-1] = 'N';
    }
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
                    printf("|  ");
                }
        }
        printf("|\n");
    }
    printf("-----------------------\n");
}

GRID copieGRID(GRID gModel) {
    GRID g = reservationMemoire(gModel.size_grid - 2);
    for(int i = 0; i<gModel.size_grid; i++) {
        for(int j = 0; j<gModel.size_grid; j++) {
            g.board[i][j] = gModel.board[i][j];
        }
    }
    return g;
}

void whereCanIPlay(GRID g, char myColor) {
    GRID gTemp = copieGRID(g);

    for(int i = 1; i<g.size_grid-1; i++) {
        for(int j = 1; j<g.size_grid-1; j++) {
                if(g.board[i][j] == myColor) {
                    isNeigbourAdversary(gTemp,i,j,myColor);
                }

        }
    }


}

void isNeigbourAdversary(GRID g, int xPos, int yPos, char myColor) {
    char adversaryColor;
    if( myColor == 'W') {
        adversaryColor = 'B';
    } else {
        adversaryColor = 'W';
    }
    printf("%d, %d : %c\n", xPos, yPos, g.board[xPos][yPos]);

    for(int i = xPos - 1; i<= xPos + 1; i++) {
        for(int j = yPos - 1; j <= yPos+1; j++ ) {

            if(g.board[i][j] == adversaryColor) {
                DIRECTION dir = defineDIRECTION(xPos,yPos,i,j);
                canIPlay(g,dir,xPos,yPos,myColor);
            }
        }
    }
}

DIRECTION defineDIRECTION(int xPos, int yPos, int i, int j){
    DIRECTION dir = NULL;
    if(xPos - i == 1) {

        if(yPos - j == 1) {
            dir = NE;
        } else {
            if(yPos - j == -1) {
                dir = NW;
            } else {
                if(yPos == 0) {
                    dir = NORTH;
                } else {
                    printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
                }
            }
        }

    } else {
        if(xPos - i == -1) {

                if(yPos - j == 1) {
                    dir = SE;
                } else {
                    if(yPos - j == -1) {
                        dir = SW;
                    } else {
                        if(yPos == 0) {
                            dir = SOUTH;
                        } else {
                            printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
                        }
                    }
                }

        } else {
            if(xPos - i == 0) {
                    if(yPos - j == 1) {
                        dir = EAST;
                    } else {
                        if(yPos - j == -1) {
                            dir = WEST;
                        } else {
                            printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
                        }
                    }

            } else {
             printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
            }
        }
    }
    return dir;
}

void canIPlay(GRID g, DIRECTION dir, int xPos, int yPos, char myColor) {
    char adversaryColor;
    if( myColor == 'W') {
        adversaryColor = 'B';
    } else {
        adversaryColor = 'W';
    }

    if(g.board[xPos][yPos] == adversaryColor){
        // Go ahead

        switch(dir)
        {
            case NORTH : printf("North\n"); break;
            case SOUTH : printf("South\n"); break;
            case EAST : printf("East\n"); break;
            case WEST : printf("West\n"); break;
            case NE : printf("North East\n"); break;
            case NW : printf("North West\n"); break;
            case SE : printf("South East\n"); break;
            case SW : printf("South West\n"); break;
            default : printf("Erreur"); break;

        }
    } else {
        if(g.board[xPos][yPos] == myColor) {
            //Vant play here it's my color
            printf("Cant play its my color\n");
        } else {
            if(g.board[xPos][yPos] == '\0'){
                printf("%d,%d is a Possibilitie\n", xPos, yPos);
            }
            printf("Error canIplay() %d, %d\n", xPos, yPos);
        }
    }

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
