set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

find_package(SDL2 CONFIG REQUIRED)

include(${SOURCE_DIR}/Thirdparty/Thirdparty.cmake)
include(${SOURCE_DIR}/Runtime/Runtime.cmake)

