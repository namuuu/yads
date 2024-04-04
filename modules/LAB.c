#include <stdio.h>
#include "../bomb.h"
#include "../libs/gpio.h"
#include "modules.h"

void stike(bomb_t *bomb) ;

enum directionalButton {
    DIRECTION_DOWN = 23,
    DIRECTION_UP = 25,
    DIRECTION_LEFT = 6,
    DIRECTION_RIGHT = 24,
};

typedef struct {
    int wallUp;
    int wallRight;
    int wallDown;
    int wallLeft;
} tile_t;

typedef struct {
    int x;
    int y;
} position_t;

typedef struct {
    position_t player;
    position_t exit;
    tile_t tiles[8][8];
} labyrinth_t;



void initModuleLAB(void* bomb, int moduleId) {
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
    bomb_t* bombData = (bomb_t*) bomb;

    eteindreMatrice();

    labyrinth_t labyrinth;
    position_t player = {
        .x = 1,
        .y = 2
    };
    position_t exit = {
        .x = 1,
        .y = 3
    };

    labyrinth.tiles[0][0] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[0][1] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[0][2] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[0][3] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[0][4] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[0][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[0][6] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[0][7] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[1][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[1][1] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[1][2] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[1][3] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[1][4] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[1][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[1][6] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[1][7] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[2][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[2][1] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[2][2] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[2][3] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[2][4] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[2][5] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[2][6] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[2][7] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[3][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[3][1] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[3][2] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[3][3] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[3][4] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[3][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[3][6] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[3][7] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[4][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[4][1] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[4][2] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[4][3] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[4][4] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[4][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[4][6] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[4][7] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[5][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[5][1] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[5][2] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[5][3] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[5][4] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[5][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[5][6] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[5][7] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[6][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[6][1] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[6][2] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 0
    };
    labyrinth.tiles[6][3] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[6][4] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[6][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[6][6] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[6][7] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 0,
        .wallLeft = 1
    };
    labyrinth.tiles[7][0] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[7][1] = (tile_t) {
        .wallUp = 1,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[7][2] = (tile_t) {
        .wallUp = 0,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[7][3] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[7][4] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 1
    };
    labyrinth.tiles[7][5] = (tile_t) {
        .wallUp = 1,
        .wallRight = 0,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[7][6] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 0
    };
    labyrinth.tiles[7][7] = (tile_t) {
        .wallUp = 0,
        .wallRight = 1,
        .wallDown = 1,
        .wallLeft = 1
    };

    

    labyrinth.player = player;
    labyrinth.exit = exit;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            labyrinth.tiles[i][j].wallUp = 0;
            labyrinth.tiles[i][j].wallRight = 0;
            labyrinth.tiles[i][j].wallDown = 0;
            labyrinth.tiles[i][j].wallLeft = 0;
        }
    }

    printf("Player: %d %d\n", player.x, player.y);

    while(1) {
        // __uint8_t line1;

        // int y  = 0;
        // for(int i = 0; i < 8; i++) {
        //     if(i == player.x && y == player.y) {
        //         line1 |= 1 << i;
        //     }
        // }
        // writeSPI((__uint8_t)0, line1);


        while(!anyIsPressed());
        if(directionIsPressed(DIRECTION_UP)) {
            if(labyrinth.tiles[player.x][player.y].wallUp == 0) {
                player.y--;
            } else {
                stike(bombData);
            }
        } else if(directionIsPressed(DIRECTION_DOWN)) {
            if(labyrinth.tiles[player.x][player.y].wallDown == 0) {
                player.y++;
            } else {
                stike(bombData);
            }
        } else if(directionIsPressed(DIRECTION_LEFT)) {
            if(labyrinth.tiles[player.x][player.y].wallLeft == 0) {
                player.x--;
            } else {
                stike(bombData);
            }
        } else if(directionIsPressed(DIRECTION_RIGHT)) {
            if(labyrinth.tiles[player.x][player.y].wallRight == 0) {
                player.x++;
            } else {
                stike(bombData);
            }
        }

        printf("Player: %d %d\n", player.x, player.y);

        if(player.x == exit.x && player.y == exit.y) {
            bombData->modules[moduleId].state = INACTIVE;
            bombData->modules[moduleId].armed = DISARMED;
        }

        while(anyIsPressed());
    }    
}

void strike(bomb_t *bomb) {
    bomb->strike++;
    printf("Strike %d\n", bomb->strike);
    softToneWrite(2, 320);
    delay(150);
    softToneWrite(2, 0);
    if(bomb->strike == 3) {
        exit(0);
    }
}