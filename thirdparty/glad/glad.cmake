set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR})

project(glad-static)
add_library(glad-static STATIC ${GLAD_DIR}/include/glad/glad.h ${GLAD_DIR}/include/KHR/khrplatform.h ${GLAD_DIR}/src/glad.c)
target_include_directories(glad-static PUBLIC ${GLAD_DIR}/include)