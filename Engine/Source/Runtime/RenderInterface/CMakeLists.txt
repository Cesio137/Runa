set(RenderInterface_DIR ${CMAKE_CURRENT_LIST_DIR})

project(RenderInterface)
file(GLOB_RECURSE RenderInterface_Sources "${RenderInterface_DIR}/Public/*.h" "${RenderInterface_DIR}/Public/*.cpp" "${RenderInterface_DIR}/Private/*.h" "${RenderInterface_DIR}/Private/*.cpp")
add_library(RenderInterface STATIC ${RenderInterface_Sources})
target_include_directories(RenderInterface
        PUBLIC
        "${RenderInterface_DIR}/Public"
        PRIVATE
        "${RenderInterface_DIR}/Private"
)
target_link_libraries(RenderInterface
        PUBLIC
        Config
        SDL3::SDL3
        imgui        
)

set_target_properties(RenderInterface PROPERTIES FOLDER "Engine/Source/Runtime" LINKER_LANGUAGE CXX)

