#include "clock_config.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"

#include "board/pin_mux.h"

#include "app/tasks/blinkTask.h"

#include "system_MIMXRT1062.h"

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitBootClocks();
    BOARD_InitPins();

    SystemCoreClockUpdate();

    if (xTaskCreate(blink_task, "Blink_task", configMINIMAL_STACK_SIZE + 100, NULL, blink_task_PRIORITY, NULL) !=
        pdPASS)
    {
        while (1)
            ;
    }

    vTaskStartScheduler();

    for (;;)
        ;
}
