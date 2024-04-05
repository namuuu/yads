#include <stdio.h>
#include "../bomb.h"
#include "../libs/gpio.h"
#include "modules.h"

void initSPIDec();
void deacSPIDec();
void writeSPIDec(__uint8_t addr, __uint8_t data);
void dessinDec();

void initModuleDEC(void* bomb, int moduleId) {
    bomb_t* bombData = (bomb_t*) bomb;
    wiringPiSetup();
    int fd = wiringPiSPISetup(0, 500000);
    if (fd == -1) {
        printf("Erreur SPI\n");
        return;
    }

    initSPIDec();

    int step = 0;
    int stepList[8] = {
        DIRECTION_DOWN,
        DIRECTION_LEFT,
        DIRECTION_LEFT,
        DIRECTION_DOWN,
        DIRECTION_RIGHT,
        DIRECTION_LEFT,
        DIRECTION_RIGHT,
        DIRECTION_UP
    };


    while(1) {
        dessinDec();

        while(!anyIsPressed());
        

        // Check if step should advance
        if(directionIsPressed(stepList[step]) == 1) {
            step++;
            if(step == 8) {
                bombData->modules[moduleId].state = INACTIVE;
                bombData->modules[moduleId].armed = DISARMED;
                deacSPIDec();
                while(1);
            }
        } else {
            if(step != 0 && directionIsPressed(stepList[step - 1] == 1))
                continue;
            bombData->strike++;
            if(bombData->strike == 3) {
                //bombData->timer.state = EXPLODED;
                deacSPIDec();
                exit(EXIT_FAILURE);
            }
            step = 0;
        }

        while(anyIsPressed());
    }
}

/**
 * @fn void initSPIDec();
 * @brief Initialisation du bus SPI
*/
void initSPIDec() {
    // Init PIN 11 en sortie
    pinMode(11, OUTPUT);
    // Decode mode
    writeSPIDec(0x09, 0x00);
    // Luminosité
    writeSPIDec(0x0A, 0x03);
    // Scan limit
    writeSPIDec(0x0B, 0x07);
    // Allumer le composant
    writeSPIDec(0x0C, 0x01);
}

void deacSPIDec() {
    writeSPI(0x0C, 0x00);
}

/**
 * @fn void writeSPIDec(__uint8_t addr, __uint8_t data);
 * @brief Ecriture sur le bus SPI
 * @param addr Adresse du registre
 * @param data Donnée à écrire
*/
void writeSPIDec(__uint8_t addr, __uint8_t data) {

    // Création d'un tableau pour l'envoi des données dans la même trame
    __uint8_t dataToSend[2] = {addr, data};

    digitalWrite(11, LOW);
    wiringPiSPIDataRW(0, dataToSend, 2);
    digitalWrite(11, HIGH);
}

/**
 * @fn void dessinDec();
 * @brief Dessin de la matrice de LED à l'aide de valeurs hexadécimales
*/
void dessinDec() {
    // Colonne 0 à 7
    int lines[8] = {
        0xe4, 0x6a, 0x6a, 0xe4, 0xf0, 0x6a, 0xf0, 0xcf
    };

    // up = 0xcf left = 0x6a down = 0xe4 right = 0xf0
    for (int i = 0; i < 8; i++) {
        // print line in binary
        // printf("%d\n", lines[i]);
        writeSPIDec(i+1, lines[i]);
    }
}