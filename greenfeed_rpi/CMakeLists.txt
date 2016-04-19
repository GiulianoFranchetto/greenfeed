cmake_minimum_required(VERSION 3.3)
project(greenfeed_rpi)

set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(includes)
set(SOURCE_FILES main.cpp Regulateur.cpp includes/Regulateur.h UsbComm.cpp includes/UsbComm.h base64.cpp includes/base64.h)
add_executable(greenfeed_rpi ${SOURCE_FILES})
target_link_libraries(greenfeed_rpi pthread)
target_link_libraries(greenfeed_rpi libmodbus.so)