#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "textcolor.h"

#include "libs/data.h"
#include "libs/gpio.h"
#include "modules/modules.h"
#include "libs/menuLib.h"

typedef struct {
    int code;
    char* args[10];
    int nbArgs;
} send_t;

typedef struct {
    int code;
    char* args[10];
    int nbArgs;
} received_t;

/* ---------------------------------------  PROTOTYPES  ------------------------------------------ */

int timer();

void initBomb();

void initModules();
int initTimer();

int activateModule(int moduleId);
void deactivateModule();

void clientMonitor(socket_t sock) ;
void deserial(generic quoi, char *msg);
void serial(generic quoi, char* req) ;

