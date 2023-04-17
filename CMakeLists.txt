CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

SET(MCUX_SDK_HOME "$ENV{MCUX_SDK_HOME}")
SET(CMAKE_TOOLCHAIN_FILE "${MCUX_SDK_HOME}/core/tools/cmake_toolchain_files/armgcc.cmake")

SET(CMAKE_BUILD_TYPE "flexspi_nor_release")

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(PROJECT_NAME "Sandbox")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# arm-none-eabi-objcopy -O ihex ./Sandbox.elf ./Sandbox.hex

project(${PROJECT_NAME})

set(MCUX_SDK_PROJECT_NAME ${PROJECT_NAME}.elf)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME}
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/board.c
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/clock_config.c
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/dcd.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/board/board.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/board/clock_config.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/board/dcd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/board/pin_mux.c
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/semihost_hardfault.c
    ${CMAKE_CURRENT_SOURCE_DIR}/xip/evkbmimxrt1060_flexspi_nor_config.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060
    ${CMAKE_CURRENT_SOURCE_DIR}/xip
    ${CMAKE_CURRENT_SOURCE_DIR}/board
)
# <sdkComponents>platform.drivers.igpio.MIMXRT1062;platform.drivers.clock.MIMXRT1062;platform.drivers.common.MIMXRT1062;device.MIMXRT1062_CMSIS.MIMXRT1062;utility.debug_console.MIMXRT1062;component.lpuart_adapter.MIMXRT1062;component.serial_manager.MIMXRT1062;component.lists.MIMXRT1062;component.serial_manager_uart.MIMXRT1062;platform.drivers.lpuart.MIMXRT1062;device.MIMXRT1062_startup.MIMXRT1062;platform.drivers.iomuxc.MIMXRT1062;platform.utilities.assert.MIMXRT1062;platform.drivers.xip_device.MIMXRT1062;platform.drivers.xip_board.evkbmimxrt1060.MIMXRT1062;CMSIS_Include_core_cm.MIMXRT1062;platform.utilities.misc_utilities.MIMXRT1062;device.MIMXRT1062_system.MIMXRT1062;evkbmimxrt1060_iled_blinky;</sdkComponents>
set(CMAKE_MODULE_PATH
    ${MCUX_SDK_HOME}/core
)

include(all_devices)
include(device_startup)
include(driver_xip_device)
include(driver_clock)
include(driver_igpio)
include(driver_lpuart)
include(component_lists)
include(component_serial_manager)
include(component_lpuart_adapter)
include(utility_assert_lite)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()  

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)
