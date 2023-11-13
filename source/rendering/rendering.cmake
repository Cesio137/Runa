set(Rendering_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Rendering)
file(GLOB_RECURSE Rendering_Sources "${Rendering_DIR}/public/*.h" "${Rendering_DIR}/private/*.h" "${Rendering_DIR}/public/*.cpp" "${Rendering_DIR}/private/*.cpp")
add_library(Rendering STATIC ${Rendering_Sources})
target_include_directories(Rendering
        PUBLIC
        "${Rendering_DIR}/public"
        PRIVATE
        "${Rendering_DIR}/private"
        INTERFACE
        "${Rendering_DIR}/public"
        "${Rendering_DIR}/private"
)
target_link_libraries(Rendering
        Core
        Render_Interface
)
