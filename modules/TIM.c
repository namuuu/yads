#include "../bomb.h"
#include "modules.h"

void initModuleTIM(void* bomb, int moduleId) {
    bomb_t* bombData = (bomb_t*) bomb;

    // Wait for key19
    while(digitalRead(19) == 0) {
        delay(100);
    }

    // Obtain last digit of timer
    int lastDigit = bombData->timer.value % 10;

    // Check if last digit is valid
    if(lastDigit == 4) {
        bombData->modules[moduleId].state = DISARMED;
        while(1);
    } else {
        bombData->strike++;
        if(bombData->strike == 3) {
            exit(0);
        }

        // Wait for release of key19
        while(digitalRead(19) == 1) {
            delay(100);
        }
    }
    
}