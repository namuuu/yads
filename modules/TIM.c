#include "../bomb.h"
#include "../libs/gpio.h"
#include "modules.h"


#define CORRECT_DIGIT 4

void initModuleTIM(void* bomb, int moduleId) {
    bomb_t* bombData = (bomb_t*) bomb;

    eteindreMatrice();

    while(1) {

        // Wait for key19
        while(!anyIsPressed());

        // Obtain last digit of timer
        int lastDigit = bombData->timer.value % 10;

        // Check if last digit is valid
        if(lastDigit == CORRECT_DIGIT) {
            bombData->modules[moduleId].state = INACTIVE;
            bombData->modules[moduleId].armed = DISARMED;
            printf("Disarmed\n");
            exit(EXIT_SUCCESS);
        } else {
            bombData->strike++;
            if(bombData->strike == 3) {
                exit(0);
            }

            // Wait for release of key19
            while(anyIsPressed());
        }
    }
    
}