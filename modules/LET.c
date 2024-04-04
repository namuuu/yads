#include <stdio.h>
#include "../bomb.h"
#include "../libs/gpio.h"
#include "modules.h"

void anyLetterPressed();
void anyLetterUnpressed();

void initModuleLET(void* bomb, int moduleId) {
    printf("%d\n", moduleId);
    bomb_t* bombData = (bomb_t*) bomb;

    int stepList[3] = { 2, 1, 2 }; // List of the correct steps to input
    int step = 0; // Which step the user is on

    allumerMatrice();

    while(1) {
        anyLetterPressed();

        // Check if step should advance
        if(locationIsPressed(stepList[step] - 1, 0) == 1) {
            step++;
            if(step == 3) {
                bombData->modules[moduleId].state = INACTIVE;
                bombData->modules[moduleId].armed = DISARMED;
                while(1);
            }
        } else {
            bombData->strike++;
            if(bombData->strike == 3) {
                //bombData->timer.state = EXPLODED;
                exit(EXIT_FAILURE);
            }
            step = 0;
        }

        anyLetterUnpressed();
    }
    



    
}

void anyLetterPressed() {
    while(1) {
        for(int i = 0; i < 4; i++) {
            if(locationIsPressed(i, 0) == 1) {
                return;
            }
        }
    }
}

void anyLetterUnpressed() {
    while(1) {
        for(int i = 0; i < 4; i++) {
            if(locationIsPressed(i, 0) == 0) {
                return;
            }
        }
    }
}