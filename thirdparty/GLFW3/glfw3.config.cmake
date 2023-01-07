set(GLFW3_DIR ${CMAKE_CURRENT_LIST_DIR})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${GLFW3_DIR}/glfw/include)
add_subdirectory(${GLFW3_DIR}/glfw)

