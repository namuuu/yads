#include <stdio.h>
#include "../bomb.h"
#include "modules.h"

void initModuleLET(void* bomb, int moduleId) {
    bomb_t* bombData = (bomb_t*) bomb;

    int stepList[3] = { 2, 1, 2 }; // List of the correct steps to input
    int step = 0; // Which step the user is on

    while(1) {
        // Get the key pressed between pins 1 and 5
        int key = 0;
        for(int i = 0; i < 4; i++) {
            key |= digitalRead(i) << i;
        }

        // Check if step should advance
        if(key == stepList[step]) {
            step++;
            if(step == 3) {
                bombData->modules[moduleId].state = DISARMED;
                while(1);
            }
        } else if(key != 0) {
            bombData->strike++;
            if(bombData->strike == 3) {
                bombData->timer.state = EXPLODED;
                exit(EXIT_FAILURE);
            }
            step = 0;
        }
    }
    



    
}