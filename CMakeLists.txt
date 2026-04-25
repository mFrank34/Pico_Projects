cmake_minimum_required(VERSION 3.13)

# Force ARM toolchain before anything else
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(my_pico_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(src)