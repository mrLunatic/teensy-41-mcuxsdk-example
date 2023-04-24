#include "FreeRTOS.h"
#include "task.h"

#include "teensy.h"
#include "app/blinkTask.h"

int main(void)
{
    TEENSY_Init();

    if (blink_task_start() != pdPASS)
    {
        while (1)
            ;
    }

    vTaskStartScheduler();

    for (;;)
        ;
}
