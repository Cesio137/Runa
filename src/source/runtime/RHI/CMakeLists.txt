set(RHI_DIR ${CMAKE_CURRENT_LIST_DIR})

project(RHI)
file(GLOB_RECURSE RHI_Sources "${RHI_DIR}/*.h" "${RHI_DIR}/*.cpp")
add_library(RHI STATIC ${RHI_Sources})
target_include_directories(RHI
        PUBLIC
        "${RHI_DIR}/"
)
target_link_libraries(RHI
        Core
        Renderer
        Engine
)

set_target_properties(RHI PROPERTIES FOLDER "Source")