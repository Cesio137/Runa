set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

#Configure glad library
include(${THIRDPARTY_DIR}/glad/glad.cmake)

#Configure glfw3 library
add_subdirectory(${THIRDPARTY_DIR}/glfw3)
target_include_directories(glfw PUBLIC ${THIRDPARTY_DIR}/glfw3/include)

#Configure imgui library
project(imgui)

file(GLOB files "${THIRDPARTY_DIR}/imgui/*.h" "${THIRDPARTY_DIR}/imgui/backends/*.h" "${THIRDPARTY_DIR}/imgui/*.cpp" "${THIRDPARTY_DIR}/imgui/backends/*.cpp")
add_library(imgui STATIC ${files})
target_include_directories(imgui PUBLIC ${THIRDPARTY_DIR}/imgui ${THIRDPARTY_DIR}/imgui/backends)

#Configure vulkan library
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Vulkan target include directories: ${Vulkan_INCLUDE_DIRS}")
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
    message(STATUS "Vulkan libraries directories: ${Vulkan_LIBRARY}")
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Vulkan_LIBRARY})

else()
    message(FATAL_ERROR "You have to install vulkan sdk from 'https://vulkan.lunarg.com/sdk/home'.")

endif(Vulkan_FOUND)

#Set folder and group all thirdparty projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(glfw glad imgui PROPERTIES FOLDER thirdparty)

