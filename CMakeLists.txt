cmake_minimum_required(VERSION 3.21)
project(stm32-can-telemetry C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/sensor_node/STM32F407VG_FLASH.ld)

add_executable(sensor_node
        sensor_node/src/startup_stm32f407.c
        sensor_node/src/main.c
)

set_target_properties(sensor_node PROPERTIES SUFFIX ".elf")
set_target_properties(sensor_node PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})

target_compile_options(sensor_node
    PRIVATE
        -Wall
        -Wextra
        -ffunction-sections
        -fdata-sections
        $<$<CONFIG:Debug>:-Og;-g3>
        $<$<CONFIG:Release>:-O2>
)

target_link_options(sensor_node
    PRIVATE
        -T ${LINKER_SCRIPT}
        -Wl,--gc-sections
        -Wl,--print-memory-usage
        --specs=nano.specs
        --specs=nosys.specs
)

