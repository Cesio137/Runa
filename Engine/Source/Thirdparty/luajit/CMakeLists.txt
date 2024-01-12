set(LUA_DIR ${CMAKE_CURRENT_LIST_DIR}/${TARGET_SYSTEM})

project(LuaJit)
add_library(LuaJit INTERFACE)
target_include_directories(LuaJit
        INTERFACE
        ${LUA_DIR}/include
)

if(WIN32)
    target_link_libraries(LuaJit
            INTERFACE
            ${LUA_DIR}/lib/lua51.lib
    )
elseif(UNIX)
    target_link_libraries(LuaJit
            INTERFACE
            ${LUA_DIR}/lib/libluajit-5.1.a
    )
endif()