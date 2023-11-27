set(GLAD_DIR ${CMAKE_CURRENT_LIST_DIR})

project(glad)
add_library(glad STATIC ${GLAD_DIR}/include/glad/glad.h ${GLAD_DIR}/include/KHR/khrplatform.h ${GLAD_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_DIR}/include)

set_target_properties(glad PROPERTIES FOLDER "Thirdparty")