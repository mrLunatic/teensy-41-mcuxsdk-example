# include MCUXSDK components

# include common CMAKE file. It configures build for concrete mcu
include(all_devices)

# include device startup code
include(device_startup)

# Clock driver
include(driver_clock)

# GPIO driver
include(driver_igpio)

# XIP code. Used to flexSPI boot
include(driver_xip_device)

# XIP code. Configures flexSPI boot
include(driver_xip_board)

# FreeRTOS
include(middleware_freertos-kernel_heap_4)

# SDK debug console
include(utility_debug_console)

# USB CDC implementation. Used by debug console
include(component_serial_manager_usb_cdc)

# OS abstraction. Currenyly used by component_serial_manager_usb_cdc
include(component_osa_free_rtos)
