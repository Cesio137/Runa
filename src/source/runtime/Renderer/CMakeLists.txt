set(Renderer_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Renderer)
file(GLOB_RECURSE Renderer_Sources "${Renderer_DIR}/*.h" "${Renderer_DIR}/*.cpp")
add_library(Renderer STATIC ${Renderer_Sources})
target_include_directories(Renderer
        PUBLIC
        "${Renderer_DIR}/"
)
target_link_libraries(Renderer
        Core
        SDL2
        SDL2main
        glad
        imgui-static
)

set_target_properties(Renderer PROPERTIES FOLDER "Source")