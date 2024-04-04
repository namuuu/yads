#define INIT_TIMER 300
#define INIT_STRIKE 3

#define CHECK(sts,msg) if ((sts) == -1) {perror(msg); exit(-1);}

/* ---------------------------------------- ENUMS ---------------------------------------- */

typedef enum {
    ARMED,
    DISARMED,
} armed_t;

typedef enum {
    ACTIVE,
    INACTIVE,
} state_t;

/* ---------------------------------------  STRUCT  ------------------------------------------ */

typedef void (*moduleInitFunction_t)(void *bomb, int moduleId);

typedef struct {
    int value;
    state_t state;
} timerBomb_t;

typedef struct {
    char name[30];
    armed_t armed;
    state_t state;
    moduleInitFunction_t init;
} module_t;

typedef struct {
    timerBomb_t timer;
    armed_t armed;
    int strike;
    int activeModulepid;
    int moduleCount;
    module_t modules[30];
} bomb_t;

/* ---------------------------------------  PROTOTYPES  ------------------------------------------ */