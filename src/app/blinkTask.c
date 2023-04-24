#include "FreeRTOS.h"
#include "task.h"

#include "teensy.h"

#include "app/blinkTask.h"

#define TASK_NAME "Blink task"
#define TASK_STACK_SIZE configMINIMAL_STACK_SIZE + 100
#define TASK_PRIORITY (configMAX_PRIORITIES - 1)

void blink_task(void *pvParameters);

BaseType_t blink_task_start() {
  return xTaskCreate(blink_task, TASK_NAME, TASK_STACK_SIZE, NULL,
                     TASK_PRIORITY, NULL);
}

void show(uint32_t time) {
  TEENSY_SetLED(1U);
  vTaskDelay(time / portTICK_PERIOD_MS);

  TEENSY_SetLED(0U);
  vTaskDelay(time / portTICK_PERIOD_MS);
}

void blink_task(void *pvParameters) {
  while (true) {
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
