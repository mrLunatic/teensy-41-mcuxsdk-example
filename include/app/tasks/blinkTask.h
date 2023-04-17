#ifndef _APP_TASKS_BLINK_TASK_H_
#define _APP_TASKS_BLINK_TASK_H_

#include "FreeRTOSConfig.h"

#define blink_task_PRIORITY (configMAX_PRIORITIES - 1)

void blink_task(void *pvParameters);

#endif
