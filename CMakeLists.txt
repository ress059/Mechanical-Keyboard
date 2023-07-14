cmake_minimum_required(VERSION 3.22)
project(Keyboard)

set(MCU "atmega32u4" CACHE STRING "Target microcontroller")

# Add build targets for each supported microcontroller

if (mmcu flag certain value)
    add_library(
        bsp_atmeag32u4 STATIC
        src/drivers/atmel/avr/megaavr/atmegaxxu4/gpio.c
        src/drivers/atmel/avr/megaavr/atmegaxxu4/gpio.h
    )
endif()

add_executable(${PROJECT_NAME}_${MCU} src/mainapp/)
target_compile_options(${PROJECT_NAME}_${MCU} PRIVATE -mmcu=${MCU}) # TODO: Other compiler options


