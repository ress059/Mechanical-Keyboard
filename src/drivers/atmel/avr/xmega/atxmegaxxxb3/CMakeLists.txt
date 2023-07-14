# Generates a Static Library for the ATMega16U4 and ATMega32U4 builds. If these MCUs are build then this
# library will be statically linked.

add_library(
    bsp_atxmegaxxxb3 STATIC
    gpio.h
    gpio.c
    # TODO: Add watchdog and timers when ready!
)

target_include_directories(atxmegaxxxb3 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
