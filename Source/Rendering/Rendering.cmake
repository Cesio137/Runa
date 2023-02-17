set(Rendering_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Rendering)
file(GLOB_RECURSE Rendering_Sources "*.h" "*.cpp")
add_library(Rendering STATIC ${Rendering_Sources})
target_include_directories(Rendering 
        PUBLIC 
        "${Rendering_DIR}/Public"
        PRIVATE
        "${Rendering_DIR}/Private"
        INTERFACE
        "${Rendering_DIR}/Private"
)
target_link_libraries(Rendering         
        PRIVATE
        Source_Interface
)

