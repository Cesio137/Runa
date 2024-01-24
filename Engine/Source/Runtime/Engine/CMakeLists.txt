set(Engine_DIR ${CMAKE_CURRENT_LIST_DIR})

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
        SDL2

)

set_target_properties(Engine PROPERTIES FOLDER "Engine/Source/Runtime")