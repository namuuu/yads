#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
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