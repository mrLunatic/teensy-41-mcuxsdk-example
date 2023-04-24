# Include reusable code from evk board files

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060
)

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE 
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/board.c
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/clock_config.c
    ${MCUX_SDK_HOME}/core/boards/evkmimxrt1060/dcd.c
)