CMAKE_MINIMUM_REQUIRED (VERSION 3.10.0)

# MCXUSDK home directory
SET(MCUX_SDK_HOME "$ENV{MCUX_SDK_HOME}")

# Toolchain file
SET(CMAKE_TOOLCHAIN_FILE "${MCUX_SDK_HOME}/core/tools/cmake_toolchain_files/armgcc.cmake")

# Enable processing assembler files
ENABLE_LANGUAGE(ASM)

# Set directory to search sdk *.cmake files
SET(CMAKE_MODULE_PATH "${MCUX_SDK_HOME}/core")

# Project duild type (flexspi_nor_release | flexspi_nor_debug)
SET(CMAKE_BUILD_TYPE "flexspi_nor_release")

# elf file output directory
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)

# hex file output directoy
SET(HEX_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# use current directory name as project name
GET_FILENAME_COMPONENT(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# replace whitespaces in project name
STRING(REPLACE " " "_" PROJECT_NAME ${PROJECT_NAME})

# Project mcuxsdk priject name. (!) This variable used by SDK components
SET(MCUX_SDK_PROJECT_NAME ${PROJECT_NAME}.elf)

# Creating CMAKE project
PROJECT(${PROJECT_NAME})

# Create executable target
ADD_EXECUTABLE(${MCUX_SDK_PROJECT_NAME})

# Add headers directory to executable target
TARGET_INCLUDE_DIRECTORIES(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add source files to executable target
TARGET_SOURCES(${MCUX_SDK_PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/blinkTask.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/teensy.c
)

# Include CMAKE files
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Board.cmake)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Flags.cmake)
INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Components.cmake)

# Some magic
IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)  
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")  
ENDIF()
TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)
TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})
TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

# Ensure hex file output directory
FILE(MAKE_DIRECTORY ${HEX_OUTPUT_PATH})

# Convert elf to hex
ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.elf ${HEX_OUTPUT_PATH}/${PROJECT_NAME}.hex
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating hex"
)
