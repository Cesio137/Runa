set(Launcher_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Launcher)
file(GLOB_RECURSE Launcher_Sources "${Launcher_DIR}/public/*.h" "${Launcher_DIR}/private/*.h" "${Launcher_DIR}/public/*.cpp" "${Launcher_DIR}/private/*.cpp" ${Font_Files})
add_library(Launcher STATIC ${Launcher_Sources})
target_include_directories(Launcher
        PUBLIC
        "${Launcher_DIR}/public"
        INTERFACE
        "${Launcher_DIR}/public"
)
target_link_libraries(Launcher
        Rendering
)