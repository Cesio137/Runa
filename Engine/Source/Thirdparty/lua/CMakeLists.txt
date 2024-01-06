set(Lua_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Lua)
file(GLOB_RECURSE Lua_Sources "${Lua_DIR}/include/*.h" "${Lua_DIR}/include/*.hpp" "${Lua_DIR}/src/*.c")
list(REMOVE_ITEM Lua_Sources "${Lua_DIR}/include/lua.h" "${Lua_DIR}/src/lua.c" "${Lua_DIR}/src/luac.c")
add_library(Lua STATIC ${Lua_Sources})
target_include_directories(Lua
        PUBLIC
        "${Lua_DIR}/include/"
)

set_target_properties(Lua PROPERTIES FOLDER "Engine/Source/Thirdparty")