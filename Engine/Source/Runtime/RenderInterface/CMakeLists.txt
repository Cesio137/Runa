set(RenderInterface_DIR ${CMAKE_CURRENT_LIST_DIR})
find_package(SDL2 CONFIG REQUIRED)

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
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        imgui
        glad
        Config


)

set_target_properties(RenderInterface PROPERTIES FOLDER "Engine/Source/Runtime" LINKER_LANGUAGE CXX)

