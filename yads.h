#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "textcolor.h"


#include "libs/gpio.h"
#include "modules/modules.h"
#include "libs/menuLib.h"

/* ---------------------------------------  PROTOTYPES  ------------------------------------------ */

int timer();

void initBomb();

void initModules();
int initTimer();

int activateModule(int moduleId);
void deactivateModule();

