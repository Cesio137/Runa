set(LUAJIT_DIR ${CMAKE_CURRENT_LIST_DIR} CACHE STRING "luajit library dir")

project(LuaJit)
file(GLOB LuaJit_Sources "${LUAJIT_DIR}/include/*.hpp" "${LUAJIT_DIR}/include/*.h" "${LUAJIT_DIR}/include/host/*.h" "${LUAJIT_DIR}/include/dynasm/*.h" "${LUAJIT_DIR}/src/*.c" "${LUAJIT_DIR}/src/host/*.c")

add_library(LuaJit STATIC ${LuaJit_Sources})
target_include_directories(LuaJit
        PUBLIC
        ${LUAJIT_DIR}/include
        PRIVATE
        ${LUAJIT_DIR}/include/host
)