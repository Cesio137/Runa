set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR})

project(glad)

file(GLOB Glad_Sources
        ${GLAD_DIR}/include/*.h
        ${GLAD_DIR}/include/EGL/*.h
        ${GLAD_DIR}/include/glad/egl.h
        ${GLAD_DIR}/include/glad/gl.h
        ${GLAD_DIR}/include/KHR/*.h
        ${GLAD_DIR}/include/vk_video/*.h

        ${GLAD_DIR}/src/egl.c
        ${GLAD_DIR}/src/gl.c
        ${GLAD_DIR}/src/vulkan.c
)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND Glad_Sources
            ${GLAD_DIR}/include/glad/glx.h

            ${GLAD_DIR}/src/glx.c
    )
endif ()

add_library(glad STATIC ${Glad_Sources})
target_include_directories(glad
        PUBLIC
        ${GLAD_DIR}/include
        ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(glad
        PUBLIC
        Config
        ${Vulkan_LIBRARIES}
)

set_target_properties(glad PROPERTIES FOLDER "Thirdparty")