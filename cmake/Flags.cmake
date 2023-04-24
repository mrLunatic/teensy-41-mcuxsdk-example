IF(NOT DEFINED FPU)
    SET(FPU "-mfloat-abi=hard -mfpu=fpv5-d16")  
ENDIF()  

IF(NOT DEFINED SPECS)
    SET(SPECS "--specs=nano.specs --specs=nosys.specs")  
ENDIF()  

# set predefined values
ADD_DEFINITIONS(
    "-DSDK_DEBUGCONSOLE=1"                      # allow debug console
    "-DSERIAL_PORT_TYPE_USBCDC=1"               # set debug console over usb cdc
    "-DDEBUG_CONSOLE_TRANSFER_NON_BLOCKING=1"   # set non-blocking data transfer
    "-DSDK_OS_FREE_RTOS"                        # using freeRTOS
    "-DOSA_USED"                                # uing OS abstraction component
    "-DPRINTF_FLOAT_ENABLE=0"
    "-DSCANF_FLOAT_ENABLE=0"
    "-DPRINTF_ADVANCED_ENABLE=0"
    "-DSCANF_ADVANCED_ENABLE=0"
)

include(${CMAKE_CURRENT_LIST_DIR}/Flags/FlexSpiNorDebug.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/Flags/FlexSpiNorRelease.cmake)