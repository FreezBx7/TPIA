#include "grid.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>


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

GRID whereCanIPlay(GRID g, char myColor) {
    GRID gTemp = copieGRID(g);

    for(int i = 1; i<g.size_grid-1; i++) {
        for(int j = 1; j<g.size_grid-1; j++) {
                if(g.board[i][j] == myColor) {
                    isNeigbourAdversary(gTemp,i,j,myColor);
                }
        }
    }
    return gTemp;

}

void isNeigbourAdversary(GRID g, int xPos, int yPos, char myColor) {
    char adversaryColor;
    if( myColor == 'W') {
        adversaryColor = 'B';
    } else {
        adversaryColor = 'W';
    }
    printf("isNeighbour adversary of : %d, %d : %c\n", xPos, yPos, g.board[xPos][yPos]);

    for(int i = xPos - 1; i<= xPos + 1; i++) {
        for(int j = yPos - 1; j <= yPos+1; j++ ) {
            if(g.board[i][j] == adversaryColor) {
                printf("%d;%d is adversary of %d;%d\n", i,j,xPos,yPos);
                DIRECTION dir = defineDIRECTION(xPos,yPos,i,j);
                canIPlay(g,dir,i,j,myColor);
            }
        }
    }
}

DIRECTION defineDIRECTION(int xPos, int yPos, int i, int j){
    DIRECTION dir = NULL;
    printf("define Direction : Me : %d;%d, Where I want to go : %d,%d\n", xPos,yPos, i,j);
    if(xPos - i == 1) {
        if(yPos - j == 1) {
            dir = NW;
        } else {
            if(yPos - j == -1) {
                dir = NE;
            } else {
                if(yPos - j == 0) {
                    dir = NORTH;
                } else {
                    printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
                }
            }
        }

    } else {
        if(xPos - i == -1) {

                if(yPos - j == 1) {
                    dir = SW;
                } else {
                    if(yPos - j == -1) {
                        dir = SE;
                    } else {
                        if(yPos - j == 0) {
                            dir = SOUTH;
                        } else {
                            printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
                        }
                    }
                }

        } else {
            if(xPos - i == 0) {
                    if(yPos - j == 1) {
                        dir = WEST;
                    } else {
                        if(yPos - j == -1) {
                            dir = EAST;
                        } else {
                            printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
                        }
                    }

            } else {
             printf("Error define Direction() %d,%d / %d,%d\n", xPos, yPos, i, j);
            }
        }
    }
    //printf("Chosen direction : %s", dir);
    return dir;
}

void canIPlay(GRID g, DIRECTION dir, int xPos, int yPos, char myColor) {
    GRID possibilityGrid = copieGRID(g);
    printf("START CAN I PLAY Where Am I : %d;%d My color : %c\t\n", xPos, yPos, myColor);
    char adversaryColor;
    if( myColor == 'W') {
        adversaryColor = 'B';
    } else {
        adversaryColor = 'W';
    }

    if(g.board[xPos][yPos] == adversaryColor){
        // Go ahead
        printf("Where I Go : ");
        switch(dir)
        {
            case NORTH : printf("North\n"); canIPlay(g, dir, xPos , yPos -1, myColor); break;
            case SOUTH : printf("South\n"); canIPlay(g, dir, xPos , yPos +1, myColor); break;
            case EAST : printf("East\n"); canIPlay(g, dir, xPos +1, yPos, myColor); break;
            case WEST : printf("West\n"); canIPlay(g, dir, xPos -1, yPos, myColor); break;
            case NE : printf("North East\n"); canIPlay(g, dir, xPos +1, yPos -1, myColor);break;
            case NW : printf("North West\n"); canIPlay(g, dir, xPos -1, yPos -1, myColor);break;
            case SE : printf("South East\n"); canIPlay(g, dir, xPos +1, yPos +1, myColor);break;
            case SW : printf("South West\n"); canIPlay(g, dir, xPos -1, yPos +1, myColor);break;
            default : printf("Erreur"); break;

        }
    } else {
        if(g.board[xPos][yPos] == myColor) {
            //Cant play here it's my color
            printf("Cant play its my color on %d,%d\n", xPos, yPos);
        } else {
            if(g.board[xPos][yPos] == '\0'){
                printf("-----  %d,%d is a Possibility ----\n", xPos, yPos);
                g.board[xPos][yPos] = 'P';
            } else {
                 printf("Error canIplay() %d, %d\n", xPos, yPos);
            }
        }
    }
}

/* Dev purposes do not use*/
GRID insertIntoGRID(GRID g,int xPos,int yPos,char myColor){
    if(g.board[xPos][yPos] != "N"){
        g.board[xPos][yPos] = myColor;
    }else{
        printf("Cant play at this position\n");
    }
    return g;
}

bool checkPossibility(GRID gPossibility, int xPos, int yPos) {


    if(gPossibility.board[xPos][yPos] == 'P') {
        return true;
    }

    return false;

}

play(GRID g, GRID gPossibility, char myColor) {
    int xPos = -1;
    int yPos = -1;

    while (!checkPossibility(gPossibility,xPos,yPos)) {
        printf("Enter positions : line and column\n");
        scanf("%d", &xPos);
        scanf("%d", &yPos);
    }

    if(checkPossibility(gPossibility,xPos,yPos)) {
        // Toutes les valeurs entre xPos yPos et les diag ligne col deviennent my color
        isThereMyColorLines(g,xPos,yPos,myColor);
    }
}

void isThereMyColor(GRID g, int xPos, int yPos, char myColor) {
    gTemp = copieGRID(g);
    for(int a = xPos + 1; a <  g.size_grid - 1; a++) {
        if(g.board[a][yPos] == myColor) {
            gTemp = changeColor(g,xPos+1,yPos,a,yPos,myColor);
        }
    }
     for(int b = xPos - 1; b > 0; b--) {
        if(g.board[b][yPos] == myColor) {
            gTemp = changeColor(g,xPos-1,yPos,b,yPos, myColor);
        }
     }
     for(int c = yPos + 1; c < g.size_grid - 1; c++) {
        if(g.board[xPos][c] == myColor) {
            gTemp = changeColor(g,xPos,yPos + 1,xPos,c, myColor);
        }
     }
     for(int d = yPos - 1; d > 0; d--) {
        if(g.board[xPos][d] == myColor) {
            gTemp = changeColor(g,xPos,yPos - 1,xPos,d, myColor);
        }
     }

     for(int e = xPos + 1; e < g.size_grid - 1; e++) {
        for(int f = yPos + 1; f < g.size_grid - 1; f++) {
            gTemp = changeColor(g,xPos + 1 ,yPos + 1,e,f, myColor);
        }
     }

     for(int h = xPos +1; h; g.size_grid - 1; h++){
        for(int i = yPos - 1, i > 0; i--){
            gTemp = changeColor(g,xPos + 1 ,yPos - 1,h,i, myColor);
        }
     }

     for(int j = xPos - 1; j > 0; j--) {
        for(int k = yPos +1; k < g.size_grid - 1; k++) {
            gTemp = changeColor(g,xPos - 1 ,yPos + 1,j,k, myColor);
        }
     }

     for(int l = xPos - 1; l > 0; l--) {
        for(int m = yPos - 1; m > 0; m--) {
            gTemp = changeColor(g,xPos - 1 ,yPos - 1,l,m, myColor);
        }
     }


}

GRID changeColor(GRID g, int xFrom, int yFrom, int xTo, int yTo, char myColor) {
    DIRECTION dir = defineDIRECTION(xFrom, yFrom, xTo, yTo);
    switch(dir)
        {
            case NORTH : printf("North\n");
                for (int a = yFrom; a > yTo; a-- ) {
                    //NORTH
                    g.board[xFrom][a] = myColor;
                }
            break;
            case SOUTH : printf("South\n");
                for( int b = yFrom; b < yTo; b++) {
                    //SOUTH
                    g.board[xFrom][b] = myColor;
                }
                break;
            case EAST : printf("East\n");
                for(int c = xFrom; c < xTo; c++) {
                    // ESAT
                    g.board[c][yFrom] = myColor;
                }
            break;
            case WEST : printf("West\n");
                for(int d = xFrom; d > xTo; d--) {
                    // WEST
                    g.board[d][yFrom] = myColor;
                }

            break;
            case NE : printf("North East\n");
                for(int e = yFrom; e > yTo; e--) {
                    for(int f = xFrom; f < xTo; f++ ) {
                        // NORTH EAST
                        g.board[f][e] = myColor;
                    }
                }
            break;
            case NW : printf("North West\n");
                for(int m = yFrom; m > yTo; m--) {
                    for(int h = xFrom; h > xTo; h--) {
                        // NORTH WEST
                        g.board[h][m] = myColor;
                    }
                }
            break;
            case SE : printf("South East\n");
                for(int i = yFrom; i < yTo; i++) {
                    for(int j = xFrom; j < xTo; j++) {
                        //SOUTH EAST
                        g.board[j][i] = myColor;
                    }
                }
            break;
            case SW : printf("South West\n");
                for(int k = yFrom; k < yTo; k++) {
                    for(int l = yFrom; l > xTo; l++) {
                        //SOUTH WEST
                        g.board[l][k] = myColor;
                    }
                }
            break;
            default : printf("Erreur"); break;

        }

        return g;
}

/* Returns true if there is a possibility false either */
bool isThereAPossibility(GRID gPossibility) { // Vérifier les fors
    for (int i = 1; i < gPossibility.size_grid - 1; i++) {
        for(int j = 0; j < gPossibility.size_grid - 1; j++ ) {
            if(gPossibility.board[i][j] == 'P') {
                return true;
            }

        }
    }
    return false;
}
