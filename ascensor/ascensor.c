#include <string.h>
#include <stdio.h>
#include "fsm.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "key.h"
#include "ascensor.h"

//Variables

portTickType now;
portTickType deadline_perid;
int control;
int B1;
int B2;

static int subiendo_pulsador_ext_2(fsm_t *fsm)
{

    return  ~(flags_key & FLAG_PULSADOR_C2) && ((now + deadline_perid) < xTaskGetTickCount()) && (flags_key & FLAG_PULSADOR_P2);
}
static int bajando_pulsador_ext_1(fsm_t *fsm)
{

    return  ~(flags_key & FLAG_PULSADOR_C1) && ((now + deadline_perid) < xTaskGetTickCount()) && (flags_key & FLAG_PULSADOR_P1);
}
static int bajando_pulsador_int_1(fsm_t *fsm)
{

    return  (flags_key & FLAG_PULSADOR_C1);
}
static int subiendo_pulsador_int_2(fsm_t *fsm)
{

    return  (flags_key & FLAG_PULSADOR_C2);
}
static int sensor_2(fsm_t *fsm)
{

    return  (flags_key & FLAG_SENSOR_A2);
}
static int sensor_1(fsm_t *fsm)
{

    return  (flags_key & FLAG_SENSOR_A1);
}
static void subir_ext_2(fsm_t *fsm)
{
    (flags_key &= ~FLAG_PULSADOR_P2);

    control = UP;
    B1 = 1;
    B2 = 1;
}
static void bajar_ext_1(fsm_t *fsm)
{
    (flags_key &= ~FLAG_PULSADOR_P1);

    control = DOWN;
    B1 = 1;
    B2 = 1;
}
static void bajar_int_1(fsm_t *fsm)
{
    (flags_key &= ~FLAG_PULSADOR_C1);
    
    control = DOWN;
    B1 = 1;
    B2 = 1;
}
static void subir_int_2(fsm_t *fsm)
{
    (flags_key &= ~FLAG_PULSADOR_C2);

    control = UP;
    B1 = 1;
    B2 = 1;
}
static void subir_int_2(fsm_t *fsm)
{
    (flags_key &= ~FLAG_PULSADOR_C2);

    control = UP;
    B1 = 1;
    B2 = 1;
}
static void subida_terminada(fsm_t *fsm)
{
    (flags_key &= ~FLAG_SENSOR_A2);
    now = xTaskGetTickCount();
    control = STOP;
    B1 = 1;
    B2 = 0;
}
static void bajada_terminada(fsm_t *fsm)
{
    (flags_key &= ~FLAG_SENSOR_A1);
    now = xTaskGetTickCount();
    control = STOP;
    B1 = 0;
    B2 = 1;
}
fsm_t *fsm_new_ascensor()
{
    deadline_perid = 10 * 1000 / portTICK_RATE_MS;
    now = xTaskGetTickCount();
    control = STOP;
    B1 = 0;
    B2 = 1;
    static fsm_trans_t ascensor_tt[] = {
        {PRIMERO, subiendo_pulsador_ext_2, MOVE, subir_ext_2},
        {PRIMERO, subiendo_pulsador_int_2, MOVE, subir_int_2},
        {MOVE, sensor_1, PRIMERO,bajada_terminada},
        {MOVE, sensor_2, SEGUNDO,subida_terminada},
        {SEGUNDO, bajando_pulsador_ext_1, MOVE, bajar_ext_1},
        {SEGUNDO, bajando_pulsador_int_1, MOVE, bajar_int_1},
        {-1, NULL, -1, NULL},
    };
    return fsm_new(ascensor_tt);
}