set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(ZLIB REQUIRED)

include(${SOURCE_DIR}/Data/Data.cmake)
include(${SOURCE_DIR}/Thirdparty/Thirdparty.cmake)
include(${SOURCE_DIR}/Runtime/Runtime.cmake)

