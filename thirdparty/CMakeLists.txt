set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

#Configure vulkan library
find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Vulkan target include directories: ${Vulkan_INCLUDE_DIRS}")
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
    message(STATUS "Vulkan libraries directories: ${Vulkan_LIBRARIES}")
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Vulkan_LIBRARIES})

else()
    message(FATAL_ERROR "You have to install vulkan sdk from 'https://vulkan.lunarg.com/sdk/home'.")

endif(Vulkan_FOUND)

#Configure glfw3 library
add_subdirectory(${THIRDPARTY_DIR}/glfw3)

#Configure glad library
include(${THIRDPARTY_DIR}/glad/glad.cmake)

#Configure imgui library
project(imgui)



if (WIN32)
    file(GLOB imgui_sources
            "${THIRDPARTY_DIR}/imgui/*.h"
            "${THIRDPARTY_DIR}/imgui/*.cpp"

            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_win32.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_win32.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx9.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx9.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx10.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx10.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx11.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx11.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx12.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_dx12.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_vulkan.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_vulkan.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl2.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl2.cpp
            )

elseif(UNIX)
    file(GLOB imgui_sources
            "${THIRDPARTY_DIR}/imgui/*.h"
            "${THIRDPARTY_DIR}/imgui/*.cpp"

            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_vulkan.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_vulkan.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl2.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl2.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_android.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_android.cpp
            )

else()
    file(GLOB imgui_sources
            "${THIRDPARTY_DIR}/imgui/*.h"
            "${THIRDPARTY_DIR}/imgui/*.cpp"

            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_osx.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_osx.mm
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_metal.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_metal.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_vulkan.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_vulkan.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_glfw.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3_loader.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl3.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl2.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_opengl2.cpp
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_android.h
            ${THIRDPARTY_DIR}/imgui/backends/imgui_impl_android.cpp
            )

endif ()

add_library(imgui ${imgui_sources})
target_include_directories(imgui PUBLIC ${THIRDPARTY_DIR}/imgui ${THIRDPARTY_DIR}/imgui/backends ${THIRDPARTY_DIR}/glfw3/include ${Vulkan_INCLUDE_DIRS})

#Configure bullet 3 library
add_subdirectory(${THIRDPARTY_DIR}/bullet3)

#Set folder and group all thirdparty projects
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(glfw glad imgui PROPERTIES FOLDER thirdparty)

