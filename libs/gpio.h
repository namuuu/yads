#include <stdio.h>
#include "../../target_wpi/include/wiringPi.h"
#include "../../target_wpi/include/wiringPiI2C.h"
#include <time.h>
#include <unistd.h>

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