set(LUA_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Lua)
file(GLOB_RECURSE Lua_Sources "${LUA_DIR}/include/*.h" "${LUA_DIR}/src/*.c")
add_library(Lua STATIC ${Lua_Sources})
target_include_directories(Lua
        PUBLIC
        "${LUA_DIR}/include"
)