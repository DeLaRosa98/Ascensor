#include "fsm.h"
#include "freertos/task.h"
#include <stdlib.h>
enum lampara_states_lampara
{
    PRIMERO,
    SEGUNDO,
    MOVE
};
enum control_estados
{
    UP,
    DOWN,
    STOP
};

fsm_t *fsm_new_ascensor();
