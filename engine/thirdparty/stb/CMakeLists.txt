set(STB_DIR ${CMAKE_CURRENT_LIST_DIR})

project(stb)
file(GLOB_RECURSE STB_SOURCES "${STB_DIR}/include/*.h" "${STB_DIR}/src/*.c")
add_library(stb STATIC ${STB_SOURCES})
target_include_directories(stb
        PUBLIC
        "${STB_DIR}/include"
)
set_target_properties(stb PROPERTIES FOLDER "/engine/thirdparty" LINKER_LANGUAGE C)