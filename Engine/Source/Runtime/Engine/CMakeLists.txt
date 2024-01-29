set(Engine_DIR ${CMAKE_CURRENT_LIST_DIR})
find_package(SDL2 CONFIG REQUIRED)

project(Engine)
file(GLOB_RECURSE Engine_Sources "${Engine_DIR}/include/*.h" "${Engine_DIR}/src/*.cpp")
add_library(Engine STATIC ${Engine_Sources})
target_include_directories(Engine
        PUBLIC
        "${Engine_DIR}/include"
)
target_link_libraries(Engine
        PUBLIC
        Core
        imgui
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>

)

set_target_properties(Engine PROPERTIES FOLDER "Engine/Source/Runtime")