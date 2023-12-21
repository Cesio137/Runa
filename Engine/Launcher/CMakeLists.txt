set(LAUNCHER_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Launcher)
file(GLOB_RECURSE Launcher_Sources "${LAUNCHER_DIR}/*.h" "${LAUNCHER_DIR}/*.cpp")
add_library(Launcher STATIC ${Launcher_Sources})
target_include_directories(Launcher
        PUBLIC
        "${LAUNCHER_DIR}/"
)
target_link_libraries(Launcher
        Core
        RHI
)