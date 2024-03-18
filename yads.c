#include <stdio.h>
#include "bomb.h"
#include "yads.h"
#include "textcolor.h"

bomb_t* bombData;

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

    while(1);

    return 0;
}

int timer() {
    int pidTimer;
    CHECK((pidTimer = fork()), "__fork__");
    if(pidTimer != 0) {
        return pidTimer;
    }

    bombData->timer.value = INIT_TIMER;

    while(bombData->timer.state == ACTIVE) {
        sleep(1);
        bombData->timer.value--;
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



