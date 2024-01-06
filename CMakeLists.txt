cmake_minimum_required(VERSION 3.24)
project(Nanometro)

set(CMAKE_CXX_STANDARD 23)

#include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

add_executable(Nanometro main.cpp)
include(config.cmake)
