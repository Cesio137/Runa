set(LUA_DIR ${CMAKE_CURRENT_LIST_DIR})

project(lua)
file(GLOB_RECURSE LUA_SOURCES "${LUA_DIR}/include/*.h" "${LUA_DIR}/src/*.c")
add_library(lua STATIC ${LUA_SOURCES})
target_include_directories(lua
        PUBLIC
        "${LUA_DIR}/include"
)
set_target_properties(lua PROPERTIES FOLDER "/engine/source/thirdparty" LINKER_LANGUAGE C)