#include <stdio.h>
#include "../../target_wpi/include/wiringPi.h"
#include "../../target_wpi/include/wiringPiI2C.h"
#include "../../target_wpi/include/wiringPiSPI.h"
#include "../../target_wpi/include/softTone.h"
#include <time.h>
#include <unistd.h>

enum directionalButton {
    DIRECTION_DOWN = 23,
    DIRECTION_UP = 25,
    DIRECTION_LEFT = 6,
    DIRECTION_RIGHT = 24,
};

void allumerMatrice();
void eteindreMatrice();

int directionIsPressed(int value);
/**
 * @fn int locationIsPressed();
 * @brief Fonction qui permet de savoir si le bouton passé en paramètre est allumé
 * @param col colonne du button
 * @param row ligne du bouton
 * @return boolean
*/
int locationIsPressed(int col, int row);
int anyIsPressed();

void writeSPI(__uint8_t addr, __uint8_t data);