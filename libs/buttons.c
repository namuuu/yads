#include "gpio.h"

int rowsPins[] = {2, 3, 21, 22}; // PIN wPi
int colsPins[] = {6, 25, 24, 23}; // PIN wPi

enum directionalButton {
    DIRECTION_DOWN = 23,
    DIRECTION_UP = 25,
    DIRECTION_LEFT = 6,
    DIRECTION_RIGHT = 24,
};

void allumerMatrice() {
    for (int i = 0; i < 4; i++) {
        // LIGNE
        pinMode(rowsPins[i], INPUT);
        pullUpDnControl(rowsPins[i], PUD_UP);
        // COLONNE
        pinMode(colsPins[i], OUTPUT);
        digitalWrite(colsPins[i], HIGH);
    }
}

void eteindreMatrice() {
    for (int i = 0; i < 4; i++) {
        // LIGNE
        pinMode(rowsPins[i], INPUT);
        pullUpDnControl(rowsPins[i], PUD_DOWN);
        // COLONNE
        pinMode(colsPins[i], INPUT);
        pullUpDnControl(colsPins[i], PUD_DOWN);
    }
}

int directionIsPressed(int value) {
    return digitalRead(value) == LOW;
}

/**
 * @fn int locationIsPressed();
 * @brief Fonction qui permet de savoir si le bouton passé en paramètre est allumé
 * @param col colonne du button
 * @param row ligne du bouton
 * @return boolean
*/
int locationIsPressed(int col, int row) {
    digitalWrite(colsPins[col], LOW);
    int level = !(digitalRead(rowsPins[row]));

    if (level == HIGH) 
        return 1;
    else 
        return 0;
}

int anyIsPressed() {
    if(directionIsPressed(DIRECTION_DOWN) || directionIsPressed(DIRECTION_UP) || directionIsPressed(DIRECTION_LEFT) || directionIsPressed(DIRECTION_RIGHT))
        return 1;
    return 0;
}
