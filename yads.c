#include <stdio.h>
#include "bomb.h"
#include "yads.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>


bomb_t* bombData;

// 0 ; 1 ; 2 ; 3 ; 4 ; 5 ; 6 ; 7 ; 8 ; 9
const int digits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

char *mainMenuChoices[] = {
                    "Modules >",
                    "Bombinfo",
                    "Quitter",
                  };  

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
    printf("Bomb armed\n");

    while(1) {
        int choix = createMenu(mainMenuChoices, sizeof(mainMenuChoices)/sizeof(mainMenuChoices[0]), "# Choix #");
        switch (choix) {
            case 0:
                printf("Modules\n");
                int moduleOk = 0;
                while(moduleOk == 0) {
                    char *modules[] = {
                        "TIM-MODULE-395",
                        "LET-MODULE-0A4"
                    };

                    for(int i = 0; i < bombData->moduleCount; i++) {
                        printf("%s %d\n", bombData->modules[i].name, i);
                        if(bombData->modules[i].armed == DISARMED) {
                            printf("Module %s is disarmed\n", bombData->modules[i].name);
                            strcat(modules[i], " (Disarmed)");
                        } else {
                            printf("Module %s is armed\n", bombData->modules[i].name);
                            strcat(modules[i], " (Armed)");
                        }

                        if(bombData->modules[i].state == ACTIVE) {
                            strcat(modules[i], " (Active)");
                        }
                    }

                    int moduleChoice = createMenu(modules, sizeof(modules)/sizeof(modules[0]), "# Modules #");
                    moduleOk = activateModule(moduleChoice);
                }
                break;
            case 1:
                printf("Bombinfo\n");
                break;
            case 2:
                printf("Quitter\n");
                kill(pidTimer, SIGKILL);
                return 0;
            default:
                break;
        }
    }

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

    // Check that the Bomb timer is active and that the time has not expired
    while(bombData->timer.state == ACTIVE && bombData->timer.value >= 0) {
        sleep(1);
        bombData->timer.value--;
        
        int storeDig[4];;

        // Store digit into digits
        storeDig[0] = bombData->timer.value % 10;
        storeDig[1] = (bombData->timer.value / 10) % 10;
        storeDig[2] = (bombData->timer.value / 100) % 10;
        storeDig[3] = (bombData->timer.value / 1000) % 10;

        wiringPiI2CWriteReg16(fd, 0x0, digits[storeDig[3]]);
        wiringPiI2CWriteReg16(fd, 0x2, digits[storeDig[2]]);
        wiringPiI2CWriteReg16(fd, 0x6, digits[storeDig[1]]);
        wiringPiI2CWriteReg16(fd, 0x8, digits[storeDig[0]]);
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
    module_t moduleTime = {
        .armed = ARMED,
        .state = INACTIVE,
        .name = "TIM-MODULE-395",
        .init = initModuleTIM
    };

    bombData->modules[bombData->moduleCount] = moduleTime;
    bombData->moduleCount++;

    module_t moduleLetter = {
        .armed = ARMED,
        .state = INACTIVE,
        .name = "LET-MODULE-0A4",
        .init = initModuleLET
    };

    bombData->modules[bombData->moduleCount] = moduleLetter;
    bombData->moduleCount++;
}

int initTimer() {
// Vérifier que wiringPi est bien initialisé
    if (wiringPiSetup() == -1) {
        printf("Erreur d'initialisation de wiringPi\n");
        exit(EXIT_FAILURE);
    }
    int fd = wiringPiI2CSetup(0x70);

    system("python libs/src.py");
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
    return 0;
}

int activateModule(int moduleId) {
    if(bombData->modules[moduleId].armed == DISARMED) {
        printf(RED "Module %s is already disarmed\n" RESET, bombData->modules[moduleId].name);
        return 0;
    }

    if(bombData->activeModulepid != 0) {
        deactivateModule();
    }

    bombData->modules[moduleId].state = ACTIVE;

    bombData->activeModulepid = fork();
    if(bombData->activeModulepid == 0) {
        bombData->modules[0].init(bombData, 0);
        exit(EXIT_SUCCESS);
    }

    return 1;
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



