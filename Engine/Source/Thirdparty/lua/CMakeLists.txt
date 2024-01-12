set(LUA_DIR ${CMAKE_CURRENT_LIST_DIR}/${TARGET_SYSTEM})

project(Lua)
add_library(Lua INTERFACE)
target_include_directories(Lua
        INTERFACE
        ${LUA_DIR}/include
)

if(WIN32)
    target_link_libraries(Lua
            INTERFACE
            ${LUA_DIR}/lib/lua.lib
    )
elseif(UNIX)
    target_link_libraries(Lua
            INTERFACE
            ${LUA_DIR}/lib/liblua.a
    )
endif()