set(Renderer_DIR ${CMAKE_CURRENT_LIST_DIR})
find_package(SDL2 CONFIG REQUIRED)

project(Renderer)
file(GLOB_RECURSE Renderer_Sources "${Renderer_DIR}/include/*.h" "${Renderer_DIR}/src/*.cpp")
add_library(Renderer STATIC ${Renderer_Sources})
target_include_directories(Renderer
        PUBLIC
        "${Renderer_DIR}/include"
)
target_link_libraries(Renderer
        PUBLIC
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        glad
        imgui
        PRIVATE
        Config

)

set_target_properties(Renderer PROPERTIES FOLDER "Engine/Source/Runtime")

