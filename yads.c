#include <stdio.h>
#include "bomb.h"
#include "yads.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "textcolor.h"

bomb_t* bombData;

// 0 ; 1 ; 2 ; 3 ; 4 ; 5 ; 6 ; 7 ; 8 ; 9
const int digits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

int main() {

    int fd = shm_open("bombData", O_CREAT | O_RDWR, S_IRWXU);  
    // Set the size of the shared memory object
    int pageSize = sysconf(_SC_PAGE_SIZE);
    CHECK(ftruncate(fd, pageSize), "__ftruncate__");
    // Map the tabEtats object into the virtual address space of the calling process
    bombData = mmap(0, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int pidTimer = timer();
    pidTimer += 1;

    initBomb();
    activateModule(0);
    
    printf("Bomb armed\n");

    int storeDig[4] = {0, 0, 0, 0};

    while(1);

    return 0;
}

int timer() {
    int fd = initTimer();
    int pidTimer;
    CHECK((pidTimer = fork()), "__fork__");
    if(pidTimer != 0) {
        return pidTimer;
    }

    bombData->timer.value = INIT_TIMER;
    clock_t startTime = clock();

    // Check that the Bomb timer is active and that the time has not expired
    while(bombData->timer.state == ACTIVE && bombData->timer.value >= 0) {
        sleep(1);
        bombData->timer.value--;
        
        int i=0;
        int storeDig[4] = {0, 0, 0, 0};

        // Store digit into digits
        // while (digit > 0) {
        //     storeDig[i] = digit % 10;
        //     digit = digit / 10;
        //     printf("storeDig[%d] = %d\n", i, storeDig[i]);
        // i++;
        storeDig[0] = bombData->timer.value % 10;
        storeDig[1] = (bombData->timer.value / 10) % 10;
        storeDig[2] = (bombData->timer.value / 100) % 10;
        storeDig[3] = (bombData->timer.value / 1000) % 10;
  }
    }

    exit(EXIT_SUCCESS);
}

void initBomb() {
    bombData->timer.state = ACTIVE;
    bombData->moduleCount = 0;
    bombData->activeModulepid = 0;

    initModules();
}

void initModules() {
    module_t moduleTest = {
        .armed = ARMED,
        .state = INACTIVE,
        .name = "TEST-078",
        .init = initModuleTest
    };

    bombData->modules[bombData->moduleCount] = moduleTest;
    bombData->moduleCount++;
}

int initTimer() {
// Vérifier que wiringPi est bien initialisé
    if (wiringPiSetup() == -1) {
        printf("Erreur d'initialisation de wiringPi\n");
        exit(EXIT_FAILURE);
    }
    int fd = wiringPiI2CSetup(0x70);
    printf("fd = %d\n", fd);

    // Allumer l'horloge
    wiringPiI2CWriteReg16(fd, 0x2, 0x1);
    // Configurer la pin INT/ROW
    wiringPiI2CWriteReg16(fd, 0xA, 0x0);
    // Allumer l'écran
    wiringPiI2CWriteReg16(fd, 0x8, 0x1);
    // Configurer la luminosité à 50%
    wiringPiI2CWriteReg16(fd, 0xE, 0x8);

    return fd;
}

void activateModule(int moduleId) {
    if(bombData->modules[moduleId].armed == DISARMED) {
        printf(RED "Module %s is already disarmed\n" RESET, bombData->modules[moduleId].name);
        return;
    }

    if(bombData->activeModulepid != 0) {
        deactivateModule();
        return;
    }

    bombData->modules[moduleId].state = ACTIVE;

    bombData->activeModulepid = fork();
    if(bombData->activeModulepid == 0) {
        bombData->modules[0].init(bombData, 0);
        exit(EXIT_SUCCESS);
    }

    return;
}

void deactivateModule() {
    for(int i = 0; i < bombData->moduleCount; i++) {
        if(bombData->modules[i].state == ACTIVE) {
            bombData->modules[i].state = INACTIVE;
        }
    }

    kill(bombData->activeModulepid, SIGKILL);
    bombData->activeModulepid = 0;
}



