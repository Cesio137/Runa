set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Source_Interface)
add_library(Source_Interface INTERFACE)
target_link_libraries(Source_Interface 
        INTERFACE 
        Qt${QT_VERSION_MAJOR}::Core
        glfw
        glad
        imgui-static
        Engine
        Rendering
)

include(${SOURCE_DIR}/Rendering/Rendering.cmake)
include(${SOURCE_DIR}/Engine/Engine.cmake)
