cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico-5110)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

if (TARGET tinyusb_device)
    add_library(lcd-5110 lcd-5110.c)

    add_executable(pico-5110 pico-5110.c)

    target_link_libraries(lcd-5110 pico_stdlib)

    # pull in common dependencies and additional i2c hardware support
    target_link_libraries(pico-5110 pico_stdlib lcd-5110 )

    # enable usb output, disable uart output
    pico_enable_stdio_usb(pico-5110 1)
    pico_enable_stdio_uart(pico-5110 0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(pico-5110)
elseif(PICO_ON_DEVICE)
    message(WARNING "not building pico-5110 because TinyUSB submodule is not initialized in the SDK")
endif()
