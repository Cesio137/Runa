set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(config)
add_subdirectory(data)
include(${SRC_DIR}/source/source.cmake)
add_subdirectory(launcher)
add_subdirectory(coreapplication)

target_link_libraries(${CMAKE_PROJECT_NAME}
        CoreApplication
        Launcher
        Core
)