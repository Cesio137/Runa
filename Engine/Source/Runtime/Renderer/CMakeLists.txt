set(Renderer_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Renderer)
file(GLOB_RECURSE Renderer_Sources "${Renderer_DIR}/include/*.h" "${Renderer_DIR}/src/*.cpp")
add_library(Renderer STATIC ${Renderer_Sources})
target_include_directories(Renderer
        PUBLIC
        "${Renderer_DIR}/include"
)
target_link_libraries(Renderer
        PUBLIC
        SDL2
        glad
        imgui
        PRIVATE
        Config

)

set_target_properties(Renderer PROPERTIES FOLDER "Engine/Source/Runtime")