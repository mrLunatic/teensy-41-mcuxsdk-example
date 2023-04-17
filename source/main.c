#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"

#include "system_MIMXRT1062.h"

volatile uint32_t g_sysTickCounter;

void SysTick_Handler(void)
{
    if (g_sysTickCounter != 0U)
    {
        g_sysTickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_sysTickCounter = n;
    while (g_sysTickCounter != 0U)
    {
    }
}

void show(uint32_t time)
{
    BOARD_LED_Set(1U);
    SysTick_DelayTicks(time);

    BOARD_LED_Set(0U);
    SysTick_DelayTicks(time);
}

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitBootClocks();
    BOARD_InitPins();

    SystemCoreClockUpdate();

    if (SysTick_Config(SystemCoreClock / 1000U))
    {
        while (1)
        {
        }
    }

    while (1)
    {
        show(150u);
        show(150u);
        show(150u);

        show(500u);
        show(500u);
        show(500u);

        show(150u);
        show(150u);
        show(150u);

        SysTick_DelayTicks(3000U);
    }
}
