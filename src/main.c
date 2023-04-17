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

    if (blink_task_start() != pdPASS)
    {
        while (1)
            ;
    }

    vTaskStartScheduler();

    for (;;)
        ;
}
