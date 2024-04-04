#include "../bomb.h"
#include "../libs/gpio.h"
#include "modules.h"


#define CORRECT_DIGIT 4

void initModuleTIM(void* bomb, int moduleId) {
    bomb_t* bombData = (bomb_t*) bomb;

    eteindreMatrice();
    softToneCreate(2);

    while(1) {

        // Wait for key19
        while(!anyIsPressed());

        // Obtain last digit of timer
        int lastDigit = bombData->timer.value % 10;

        // Check if last digit is valid
        if(lastDigit == CORRECT_DIGIT) {
            bombData->modules[moduleId].state = INACTIVE;
            bombData->modules[moduleId].armed = DISARMED;
            return;
        } else {
            bombData->strike++;
            printf("Strike %d\n", bombData->strike);
            softToneWrite(2, 320);
            delay(150);
            softToneWrite(2, 0);
            if(bombData->strike == 3) {
                exit(0);
            }

            // Wait for release of key19
            while(anyIsPressed());
        }
    }
    
}