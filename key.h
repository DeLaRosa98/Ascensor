#include <stdio.h>
#include <stdlib.h>
int key_pressed(void);
void enable_raw_mode();
void key_process(int ch);

int flags_key;

#define FLAG_PULSADOR_P1 0x01
#define FLAG_PULSADOR_P2 0x02
#define FLAG_PULSADOR_C1 0x04
#define FLAG_PULSADOR_C2 0x08
#define FLAG_SENSOR_A1 0x10
#define FLAG_SENSOR_A2 0x20
//#define FLAG_PULSADOR_LAMPARA 0x40
//#define FLAG_PULSADOR_LAMPARA  0x80
