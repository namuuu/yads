#include <stdio.h>
#include "bomb.h"
#include "yads.h"
#include "modules/modules.h"

void initModuleLAB(void* bomb, int moduleId);
bomb_t* bombData;

// 0 ; 1 ; 2 ; 3 ; 4 ; 5 ; 6 ; 7 ; 8 ; 9
const int digits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

char *mainMenuChoices[] = {
                    "Modules >",
                    "Bombinfo",
                    "Quitter",
                  };  

char *bombInfoMenu[] = {
                    "Serial number: 0AF4-21N810486-F3T4"
};

char *bombDefused[] = {
                    "Bomb defused"
};

char *bombExploded[] = {
                    "Bomb exploded"
};

int pidTimer;
int strikeBuffer;
socket_t sock;
socket_t sockClient;

int main() {
    int fd = shm_open("bombData", O_CREAT | O_RDWR, S_IRWXU);  
    // Set the size of the shared memory object
    int pageSize = sysconf(_SC_PAGE_SIZE);
    CHECK(ftruncate(fd, pageSize), "__ftruncate__");
    // Map the tabEtats object into the virtual address space of the calling process
    bombData = mmap(0, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    // Server mode
    sock = prepareForClient("0.0.0.0", 5000, SOCK_STREAM);
    // sockClient = accepterConnexion(sock);

    received_t dataReceived;
    recevoir(sock, &dataReceived, deserial);
    printf("Received data: %d\n", dataReceived.code);

    // while(1) {
    //     send_t dataSent = {
    //         .code = 1,
    //         .nbArgs = 0
    //     };
    //     envoyer(sock, &dataSent, serial);
    //     printf("Data sent\n");
    // }
    

    pidTimer = timer();

    initBomb();

    while(1) {
        int choix = createMenu(mainMenuChoices, sizeof(mainMenuChoices)/sizeof(mainMenuChoices[0]), "# Choix #");
        switch (choix) {
            case 0:
                printf("Modules\n");
                int moduleOk = 0;
                while(moduleOk == 0) {
                    char **modules = malloc(bombData->moduleCount * sizeof(char*));

                    for(int i = 0; i < bombData->moduleCount; i++) {
                        modules[i] = malloc(50 * sizeof(char));
                        strcpy(modules[i], bombData->modules[i].name);
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

                    modules[bombData->moduleCount] = "Retour";

                    for(int i = 0; i < bombData->moduleCount; i++) {
                        printf("%s\n", modules[i]);
                    }

                    int moduleChoice = createMenu(modules, bombData->moduleCount+1, "# Modules #");
                    moduleOk = activateModule(moduleChoice);
                }
                break;
            case 1:
                printf("Bombinfo\n");
                createMenu(bombInfoMenu, sizeof(bombInfoMenu)/sizeof(bombInfoMenu[0]), "# IG2I-OS - v1.08 (Experimental) #");
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

        // Buzz if timer is less than 10 sec
        softToneCreate(1);
        if(bombData->timer.value < 10) {
            softToneWrite(1, 440);
            delay(250);
            softToneWrite(1, 0);
        }

        if(bombData->timer.value == 0)
            bombData->strike = 3;
        
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

        int isBombDefused = 1;
        for(int i = 0; i < bombData->moduleCount; i++) {
            if(bombData->modules[i].armed == ARMED) {
                isBombDefused = 0;
                break;
            }
        }

        if(isBombDefused == 1) {
            bombData->timer.state = INACTIVE;
            softToneWrite(1, 320);
            delay(150);
            softToneWrite(1, 0);
            delay(150);
            softToneWrite(1, 320);
            delay(150);
            softToneWrite(1, 0);
            createMenu(bombDefused, sizeof(bombDefused)/sizeof(bombDefused[0]), "# Congrats ! #");
            exit(EXIT_SUCCESS);
        }

        if(bombData->strike >= 3) {
            bombData->timer.state = INACTIVE;
            softToneWrite(1, 500);
            delay(500);
            softToneWrite(1, 0);
            createMenu(bombExploded, sizeof(bombExploded)/sizeof(bombExploded[0]), "# Game Over #");
            exit(EXIT_SUCCESS);
        }

        if(bombData->strike != strikeBuffer) {
            strikeBuffer = bombData->strike;
            softToneWrite(1, 320);
            delay(150);
            softToneWrite(1, 0);
        }

        // Write module data in a tmpfile
        FILE *tmpFile = fopen("tmpfile", "w");
        for(int i = 0; i < bombData->moduleCount; i++) {
            fprintf(tmpFile, "%s %d\n", bombData->modules[i].name, bombData->modules[i].armed);
        }
        fclose(tmpFile);
    }

    exit(EXIT_SUCCESS);
}

void initBomb() {
    bombData->timer.state = ACTIVE;
    bombData->moduleCount = 0;
    bombData->activeModulepid = 0;
    bombData->strike = 0;

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

    module_t moduleLab = {
        .armed = ARMED,
        .state = INACTIVE,
        .name = "LAB-MODULE-PE9",
        .init = initModuleLAB
    };

    bombData->modules[bombData->moduleCount] = moduleLab;
    bombData->moduleCount++;

    module_t moduleDec = {
        .armed = ARMED,
        .state = INACTIVE,
        .name = "DEC-MODULE-404",
        .init = initModuleDEC
    };

    bombData->modules[bombData->moduleCount] = moduleDec;
    bombData->moduleCount++;

    for(int i = 0; i < bombData->moduleCount; i++) {
        printf("Module %s initialized\n", bombData->modules[i].name);
        send_t data = {
            .code = 1,
            .nbArgs = 3
        };

        data.args[0] = malloc(10 * sizeof(char));
        sprintf(data.args[0], "%d", i);
        data.args[1] = malloc(30 * sizeof(char));
        sprintf(data.args[1], "%s", "TEST");
        data.args[2] = malloc(10 * sizeof(char));
        sprintf(data.args[2], "%d", bombData->modules[i].state);

        //envoyer(sock, &data, serial);
    }
}

int initTimer() {
// Vérifier que wiringPi est bien initialisé
    if (wiringPiSetup() == -1) {
        printf("Erreur d'initialisation de wiringPi\n");
        exit(EXIT_FAILURE);
    }
    int fd = wiringPiI2CSetup(0x70);

    // Allumer l'horloge
    wiringPiI2CWrite(fd, 0x21);
    // Configurer la pin INT/ROW
    wiringPiI2CWrite(fd, 0xA0);
    // Allumer l'écran
    wiringPiI2CWrite(fd, 0x81);
    // Configurer la luminosité à 50%
    wiringPiI2CWrite(fd, 0xE7);

    return fd;
    return 0;
}

int activateModule(int moduleId) {
    if(moduleId == bombData->moduleCount) {
        return 1;
    }
    if(bombData->modules[moduleId].armed == DISARMED) {
        printf(RED "Module %s is already disarmed\n" RESET, bombData->modules[moduleId].name);
        return 0;
    }
    if(bombData->modules[moduleId].state == ACTIVE) {
        printf(RED "Module %s is already active\n" RESET, bombData->modules[moduleId].name);
        return 0;
    }

    
    deactivateModule();
    bombData->modules[moduleId].state = ACTIVE;

    bombData->activeModulepid = fork();
    if(bombData->activeModulepid == 0) {
        bombData->modules[moduleId].init(bombData, moduleId);
        softToneWrite(1, 320);
        delay(150);
        softToneWrite(1, 0);
        exit(EXIT_SUCCESS);
    }

    return 1;
}

void deactivateModule() {
    int deactivated = 0;
    for(int i = 0; i < bombData->moduleCount; i++) {
        if(bombData->modules[i].state == ACTIVE) {
            bombData->modules[i].state = INACTIVE;
            deactivated = 1;
        }
    }

    if(deactivated == 1 && bombData->activeModulepid != 0)
        kill(bombData->activeModulepid, SIGKILL);
    bombData->activeModulepid = 0;
}

/**
 * \fn void serial(generic quoi, char* req) ;
 * 
 * @brief transforme les données en chaine de charactères  
 * @param quoi 
 * @param req 
 */
void serial(generic quoi, char* req) {
    send_t transQuoi = (*(send_t*)quoi);

    sprintf(req, "%d", transQuoi.code); // Convertit le code en char
    if(transQuoi.nbArgs == 0)
        return;
    for(int i = 0; i < transQuoi.nbArgs; i++) {
        strcat(req, "-");
        strcat(req, transQuoi.args[i]);
    }
}

/**
 * \fn void deserial(generic quoi, char* msg) ;
 * 
 * @brief transforme les chaine de charactères en données
 * @param quoi 
 * @param msg 
 */
void deserial(generic quoi, char *msg) {

    // Séparer les données selon le séparateur "-" et les ranger dans une array de strings
    char *token = strtok(msg, "-");
    ((received_t*)quoi)->code = atoi(token);
    ((received_t*)quoi)->nbArgs = 0;
    token = strtok(NULL, "-");
    int i = 0;
    if(token == NULL)
        return;
    int switchToken = atoi(token);
    switch (switchToken)
    {
    default:
        while(token != NULL){
            ((received_t*)quoi)->args[i] = token;
            ((received_t*)quoi)->nbArgs++;
            token = strtok(NULL, "-");
            i++;
        }
        break;
    }
}

void clientMonitor(socket_t sock) {
    received_t data;
    while(1){
        socket_t sockClient = recevoir(sock, &data, deserial);
        printf("Received data: %d\n", data.code);
        sockClient.fd+=1;
    }
}



