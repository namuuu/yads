#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#include "modules/moduleTest.h"

/* ---------------------------------------  PROTOTYPES  ------------------------------------------ */

int timer();

void initBomb();

void initModules();

void activateModule(int moduleId);
void deactivateModule();