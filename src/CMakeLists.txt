add_executable(my_project
    main.cpp
)

target_link_libraries(my_project
    pico_stdlib
)

pico_enable_stdio_usb(my_project 1)
pico_enable_stdio_uart(my_project 0)

pico_add_extra_outputs(my_project)
