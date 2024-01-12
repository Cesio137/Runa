find_package(Vulkan REQUIRED)
add_subdirectory(Config)
add_subdirectory(Source)
add_subdirectory(Launcher)

target_link_libraries(${CMAKE_PROJECT_NAME}
        Launcher
        LuaJit
)