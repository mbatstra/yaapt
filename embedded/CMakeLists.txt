cmake_minimum_required(VERSION 3.13)

set(PICO_BOARD pico_w)

include(pico_sdk_import.cmake)

project(yaapt_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(yaapt
  src/main.c
)

pico_enable_stdio_usb(yaapt 1)
pico_enable_stdio_uart(yaapt 0)

pico_add_extra_outputs(yaapt)

target_include_directories(yaapt PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/../protocol/
  /usr/include/nanopb/
)
target_link_libraries(yaapt
  pico_stdlib
  pico_cyw43_arch_lwip_poll
)
