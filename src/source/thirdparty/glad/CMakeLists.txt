set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR})

project(glad)
file(GLOB_RECURSE Glad_Sources "${GLAD_DIR}/*.h" "${GLAD_DIR}/*.c")
add_library(glad STATIC ${Glad_Sources})
target_include_directories(glad PUBLIC ${GLAD_DIR}/include ${Vulkan_INCLUDE_DIRS})
target_link_libraries(glad
        PUBLIC
        Config
        PRIVATE
        ${Vulkan_LIBRARIES}
)

set_target_properties(glad PROPERTIES FOLDER "Thirdparty")