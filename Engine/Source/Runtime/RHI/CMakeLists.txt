set(RHI_DIR ${CMAKE_CURRENT_LIST_DIR})

project(RHI)
file(GLOB_RECURSE RHI_Sources "${RHI_DIR}/include/*.h" "${RHI_DIR}/src/*.cpp")
add_library(RHI STATIC ${RHI_Sources})
target_include_directories(RHI
        PUBLIC
        "${RHI_DIR}/include"
)
target_link_libraries(RHI
        PUBLIC
        Renderer
        Engine
)

set_target_properties(RHI PROPERTIES FOLDER "Engine/Source/Runtime")