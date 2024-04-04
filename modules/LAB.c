#include <stdio.h>
#include "../bomb.h"
#include "../libs/gpio.h"
#include "modules.h"

void strike(bomb_t *bomb) ;
void initSPI();
void writeSPI(__uint8_t addr, __uint8_t data) ;
void dessin();

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

labyrinth_t labyrinth;

void initModuleLAB(void* bomb, int moduleId) {
    printf("OOOOOOOOOOOO\n");
    bomb_t* bombData = (bomb_t*) bomb;

    eteindreMatrice();
    initSPI();

    
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
        dessin();

        while(!anyIsPressed());
        if(directionIsPressed(DIRECTION_UP)) {
            if(labyrinth.tiles[player.x][player.y].wallUp == 0) {
                player.y--;
            } else {
                strike(bombData);
            }
        } else if(directionIsPressed(DIRECTION_DOWN)) {
            if(labyrinth.tiles[player.x][player.y].wallDown == 0) {
                player.y++;
            } else {
                strike(bombData);
            }
        } else if(directionIsPressed(DIRECTION_LEFT)) {
            if(labyrinth.tiles[player.x][player.y].wallLeft == 0) {
                player.x--;
            } else {
                strike(bombData);
            }
        } else if(directionIsPressed(DIRECTION_RIGHT)) {
            if(labyrinth.tiles[player.x][player.y].wallRight == 0) {
                player.x++;
            } else {
                strike(bombData);
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

/**
 * @fn void initSPI();
 * @brief Initialisation du bus SPI
*/
void initSPI() {
    // Init PIN 11 en sortie
    pinMode(11, OUTPUT);
    // Decode mode
    writeSPI(0x09, 0x00);
    // Luminosité
    writeSPI(0x0A, 0x03);
    // Scan limit
    writeSPI(0x0B, 0x07);
    // Allumer le composant
    writeSPI(0x0C, 0x01);
}

/**
 * @fn void writeSPI(__uint8_t addr, __uint8_t data);
 * @brief Ecriture sur le bus SPI
 * @param addr Adresse du registre
 * @param data Donnée à écrire
*/
void writeSPI(__uint8_t addr, __uint8_t data) {

    // Création d'un tableau pour l'envoi des données dans la même trame
    __uint8_t dataToSend[2] = {addr, data};

    digitalWrite(11, LOW);
    wiringPiSPIDataRW(0, dataToSend, 2);
    digitalWrite(11, HIGH);
}

/**
 * @fn void dessin();
 * @brief Dessin de la matrice de LED à l'aide de valeurs hexadécimales
*/
void dessin() {
    // Colonne 0 à 7
    for (int i = 0; i < 8; i++) {
        // int line = 0;
        // for (int j = 0; j < 8; j++) {
        //     if(labyrinth.player.x == i && labyrinth.player.y == j) {
        //         printf("Player: %d %d\n", i, j);
        //         line |= 1 << j;
        //     }
        //     if(labyrinth.exit.x == i && labyrinth.exit.y == j) {
        //         printf("Exit: %d %d\n", i, j);
        //         line |= 1 << j;
        //     }
        // }
        int line = 0xCC;
        // print line in binary
        printf("%d\n", line);
        writeSPI(i+1, line);
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