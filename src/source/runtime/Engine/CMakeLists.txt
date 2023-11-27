set(Engine_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Engine)
file(GLOB_RECURSE Engine_Sources "${Engine_DIR}/*.h" "${Engine_DIR}/*.cpp")
add_library(Engine STATIC ${Engine_Sources})
target_include_directories(Engine
        PUBLIC
        "${Engine_DIR}/"
)
target_link_libraries(Engine
        PUBLIC
        Core
        imgui-static
        PRIVATE
        SDL2
        SDL2main

)

set_target_properties(Engine PROPERTIES FOLDER "Source")