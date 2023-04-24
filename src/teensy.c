#include "board.h"
#include "clock_config.h"

#include "fsl_common.h"
#include "fsl_gpio.h"
#include "fsl_iomuxc.h"

#include "usb_device_config.h"
#include "usb_phy.h"

#include "fsl_component_serial_port_usb.h"
#include "fsl_debug_console.h"

#define CONTROLLER_ID kSerialManager_UsbControllerEhci0

#define LED_GPIO GPIO2
#define LED_GPIO_PIN 3
#define LED_PIN_MUX IOMUXC_GPIO_B0_03_GPIO2_IO03
#define LED_PIN_MUX_GPIO_SEL

#define CLR_BIT(source, bitNumber) ((source) &= ~((1) << (bitNumber)))

void initLEDPin() {
  /* GPIO configuration of USER_LED on GPIO_B0_03 (pin D8) */
  gpio_pin_config_t USER_LED_config = {.direction = kGPIO_DigitalOutput,
                                       .outputLogic = 0U,
                                       .interruptMode = kGPIO_NoIntmode};

  /* Initialize GPIO functionality on GPIO_B0_03 (pin D8) */
  GPIO_PinInit(LED_GPIO, LED_GPIO_PIN, &USER_LED_config);
  IOMUXC_SetPinMux(LED_PIN_MUX, 0U);

  IOMUXC_GPR->GPR27 = CLR_BIT(IOMUXC_GPR->GPR27, LED_GPIO_PIN);
}

void BOARD_InitPins(void) {
  CLOCK_EnableClock(kCLOCK_Iomuxc);

  initLEDPin();
}

void BOARD_LED_Set(bool value) { GPIO_PinWrite(LED_GPIO, LED_GPIO_PIN, value); }

void USB_DeviceClockInit(void) {
  CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
  CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);

  usb_phy_config_struct_t phyConfig = {
      BOARD_USB_PHY_D_CAL,
      BOARD_USB_PHY_TXCAL45DP,
      BOARD_USB_PHY_TXCAL45DM,
  };

  USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ, &phyConfig);
}

void TEENSY_Init() {
  BOARD_ConfigMPU();
  BOARD_InitBootClocks();
  BOARD_InitPins();
  USB_DeviceClockInit();
  DbgConsole_Init((uint8_t)CONTROLLER_ID, (uint32_t)NULL, kSerialPort_UsbCdc,
                  (uint32_t)NULL);

  SystemCoreClockUpdate();
}

void TEENSY_SetLED(bool value) { GPIO_PinWrite(LED_GPIO, LED_GPIO_PIN, value); }
