cmake_minimum_required(VERSION 3.15)

# Generic system target avoids running host sanity checks
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Target toolchain binaries
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_SIZE    arm-none-eabi-size)

project(logic_analyzer VERSION 1.0 LANGUAGES C)

# Core architectural and compilation flags
set(CPU_FLAGS -mcpu=cortex-m3 -mthumb)
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -Wextra -O2 -ffreestanding")

# Source definition matching your tree
set(SOURCES
    src/main.c
    stm32f103c8t6_startup.c
)

add_executable(firmware.elf ${SOURCES})

target_include_directories(firmware.elf PRIVATE src/inc)

# Linker flags: direct script usage
target_link_options(firmware.elf PRIVATE
    ${CPU_FLAGS}
    -T${CMAKE_CURRENT_SOURCE_DIR}/stm32f103c8t6.ld
    -nostdlib
    -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/firmware.map
)

# Track linker script modifications to trigger automatic relink
set_target_properties(firmware.elf PROPERTIES
    LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/stm32f103c8t6.ld
)

# Post-build: generate raw binary and output section sizes
add_custom_command(TARGET firmware.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary firmware.elf firmware.bin
    COMMAND ${CMAKE_SIZE} firmware.elf
    COMMENT "Generating raw binary and printing section sizes"
)

# Flash automation target
set(SERIAL_PORT "/dev/ttyUSB0" CACHE STRING "Serial port for flashing")
set(BAUD_RATE "115200" CACHE STRING "Baudrate for stm32flash")

add_custom_target(flash
    COMMAND stm32flash -b ${BAUD_RATE} -w firmware.bin -v -g 0x0 ${SERIAL_PORT}
    DEPENDS firmware.elf
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    USES_TERMINAL
    COMMENT "Flashing firmware.bin to STM32 via ${SERIAL_PORT}"
)
