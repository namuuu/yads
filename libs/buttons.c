#include "gpio.h"

int rowsPins[] = {2, 3, 21, 22}; // PIN wPi
int colsPins[] = {6, 25, 24, 23}; // PIN wPi

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

void initSPI() {
    pinMode(11, OUTPUT);
    writeSPI(0x09, 0x00);
    writeSPI(0x0A, 0x03);
    writeSPI(0x0B, 0x07);
    writeSPI(0x0C, 0x01);
}

void writeSPI(_uint8_t addr, _uint8_t data) {
    __uint8_t dataToSend[2] = {addr, data};
    digitalWrite(11, LOW);
    wiringPiSPIDataRW(0, dataToSend, 2);
    digitalWrite(11, HIGH);

}
