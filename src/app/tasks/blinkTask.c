#include "clock_config.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "board/pin_mux.h"

#include "app/tasks/blinkTask.h"

#include "system_MIMXRT1062.h"

#define blink_task_PRIORITY (configMAX_PRIORITIES - 1)

void show(uint32_t time)
{
    BOARD_LED_Set(1U);
    vTaskDelay(time / portTICK_PERIOD_MS);

    BOARD_LED_Set(0U);
    vTaskDelay(time / portTICK_PERIOD_MS);
}

void blink_task(void *pvParameters)
{
    while (true)
    {
        show(70u);
        show(70u);
        show(70u);

        show(150u);
        show(150u);
        show(150u);

        show(70u);
        show(70u);
        show(70u);

        vTaskDelay(3000U / portTICK_PERIOD_MS);
    }
}
