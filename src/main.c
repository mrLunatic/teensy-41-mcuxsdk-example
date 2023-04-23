#include "clock_config.h"
#include "board.h"

#include "FreeRTOS.h"
#include "task.h"
#include "fsl_debug_console.h"
#include "fsl_component_serial_port_usb.h"

#include "board/pin_mux.h"

#include "app/tasks/blinkTask.h"

#include "system_MIMXRT1062.h"

#include "usb_device_config.h"
#include "usb_phy.h"

#define CONTROLLER_ID kSerialManager_UsbControllerEhci0

void USB_DeviceClockInit(void)
{
    CLOCK_EnableUsbhs0PhyPllClock(kCLOCK_Usbphy480M, 480000000U);
    CLOCK_EnableUsbhs0Clock(kCLOCK_Usb480M, 480000000U);

    usb_phy_config_struct_t phyConfig = {
        BOARD_USB_PHY_D_CAL,
        BOARD_USB_PHY_TXCAL45DP,
        BOARD_USB_PHY_TXCAL45DM,
    };

    USB_EhciPhyInit(CONTROLLER_ID, BOARD_XTAL0_CLK_HZ, &phyConfig);
}

int main(void)
{
    BOARD_ConfigMPU();
    BOARD_InitBootClocks();
    BOARD_InitPins();
    USB_DeviceClockInit();
    DbgConsole_Init((uint8_t)CONTROLLER_ID, (uint32_t)NULL, kSerialPort_UsbCdc, (uint32_t)NULL);

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
