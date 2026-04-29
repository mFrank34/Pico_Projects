cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico2_w)
set(PICO_PLATFORM rp2350) # Good practice to be explicit

include(pico_sdk_import.cmake)
project(test_project C CXX ASM)

pico_sdk_init()

file(GLOB MODULES_SOURCE
        src/Module/*.cpp
)

add_executable(test_project
        src/Main.cpp
        ${MODULES_SOURCE}
)

target_link_libraries(test_project
        pico_stdlib
        hardware_adc
        pico_cyw43_arch_none
)

# Only generate the file you need to flash
pico_add_uf2_output(test_project)

# Enable usb output, disable uart output
pico_enable_stdio_usb(test_project 1)
pico_enable_stdio_uart(test_project 0)