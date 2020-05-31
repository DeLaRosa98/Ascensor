#include <stdio.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "fsm.h"
#include "ascensor.h"


static void lampara_principal(void *ignore)
{
    static int frame = 0;

    fsm_t *ascensor_fsm = fsm_new_lampara();
   
    portTickType period = 20 / portTICK_RATE_MS;
    portTickType last = xTaskGetTickCount();

    // Para poder usar el terminal correctamnte
    enable_raw_mode();

    
    while (1)
    {
        if (key_pressed())
        {
            key_process(getchar());
        }
       fsm_fire(ascensor_fsm);
               vTaskDelayUntil(&last, period);
    }
}

void user_init(void)
{
    xTaskHandle task_lampara;
    xTaskCreate(lampara_principal, (const signed char *)"reloj", 2048, NULL, 1, &task_lampara);
}

void vApplicationIdleHook(void) {}
void vMainQueueSendPassed(void) {}

int main(void)
{
    flags_key = 0;
    user_init();
    vTaskStartScheduler();
    return 1;
}
