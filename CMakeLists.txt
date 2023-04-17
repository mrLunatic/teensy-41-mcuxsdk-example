CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

SET(MCUX_SDK_HOME "$ENV{MCUX_SDK_HOME}")
SET(CMAKE_TOOLCHAIN_FILE "${MCUX_SDK_HOME}/core/tools/cmake_toolchain_files/armgcc.cmake")

SET(CMAKE_BUILD_TYPE "flexspi_nor_release")

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(PROJECT_NAME "Sandbox")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
SET(HEX_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY ${HEX_OUTPUT_PATH})

# arm-none-eabi-objcopy -O ihex ./Sandbox.elf ./Sandbox.hex

project(${PROJECT_NAME})

set(MCUX_SDK_PROJECT_NAME ${PROJECT_NAME}.elf)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Flags.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME}
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/board.c
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/clock_config.c
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/dcd.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/board/pin_mux.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_MODULE_PATH
    ${MCUX_SDK_HOME}/core
)

include(all_devices)
include(device_startup)
include(driver_clock)
include(driver_xip_device)
include(driver_xip_board)
include(driver_igpio)
include(utility_debug_console_lite)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

add_custom_command(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${CMAKE_CURRENT_BINARY_DIR}/bin/${PROJECT_NAME}.elf ${CMAKE_CURRENT_SOURCE_DIR}/bin/${PROJECT_NAME}.hex
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating hex"
)
