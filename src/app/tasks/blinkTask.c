#include "clock_config.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "board/pin_mux.h"

#include "app/tasks/blinkTask.h"

#include "system_MIMXRT1062.h"

#include "fsl_debug_console.h"

#define TASK_NAME "Blink task"
#define TASK_STACK_SIZE configMINIMAL_STACK_SIZE + 100
#define TASK_PRIORITY (configMAX_PRIORITIES - 1)

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
        PRINTF("SOS\n");
        
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

BaseType_t blink_task_start()
{
    return xTaskCreate(blink_task, TASK_NAME, TASK_STACK_SIZE, NULL, TASK_PRIORITY, NULL);
}
