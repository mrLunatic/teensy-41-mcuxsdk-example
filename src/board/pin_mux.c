#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "fsl_gpio.h"

#include "board/pin_mux.h"

#define LED_GPIO GPIO2
#define LED_GPIO_PIN 3
#define LED_PIN_MUX IOMUXC_GPIO_B0_03_GPIO2_IO03
#define LED_PIN_MUX_GPIO_SEL

#define CLR_BIT(source, bitNumber) ((source) &= ~((1) << (bitNumber)))

void initLEDPin()
{
    /* GPIO configuration of USER_LED on GPIO_B0_03 (pin D8) */
    gpio_pin_config_t USER_LED_config = {
        .direction = kGPIO_DigitalOutput,
        .outputLogic = 0U,
        .interruptMode = kGPIO_NoIntmode};

    /* Initialize GPIO functionality on GPIO_B0_03 (pin D8) */
    GPIO_PinInit(LED_GPIO, LED_GPIO_PIN, &USER_LED_config);
    IOMUXC_SetPinMux(LED_PIN_MUX, 0U);

    IOMUXC_GPR->GPR27 = CLR_BIT(IOMUXC_GPR->GPR27, LED_GPIO_PIN);
}

void BOARD_InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);

    initLEDPin();
}

void BOARD_LED_Set(bool value)
{
    GPIO_PinWrite(LED_GPIO, LED_GPIO_PIN, value);
}
