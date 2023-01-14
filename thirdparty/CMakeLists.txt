set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

#
# CHECK IF SPECIFIC THIRDPARTY DEPENDENCIES IS INSTALLED
#

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

#
# DOWNLOAD THIRDPARTY DEPENDENCIES
#

include(FetchContent)

#set(FETCHCONTENT_BASE_DIR ${THIRDPARTY_DIR})

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG        7482de6071d21db77a7236155da44c172a7f6c9e # 3.3.8
      )
  
    FetchContent_MakeAvailable(glfw)
    #add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
endif()

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        d7c8516a4b848c0291e3d75b627c0843f515f591 # 1.89.2
      )
  
    FetchContent_MakeAvailable(imgui)
    #add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR})
endif()

FetchContent_GetProperties(Bullet)
if(NOT Bullet_POPULATED)
    FetchContent_Declare(
        Bullet
        GIT_REPOSITORY https://github.com/bulletphysics/bullet3.git
        GIT_TAG        7dee3436e747958e7088dfdcea0e4ae031ce619e # 3.2.4
      )
  
    FetchContent_MakeAvailable(Bullet)
endif()


#
# CONFIGURE THIRDPARTY LIBRARIES
#

#Configure glad library
include(${THIRDPARTY_DIR}/glad/glad.cmake)

#Configure imgui library

if (WIN32)
    file(GLOB imgui_sources
            ${imgui_SOURCE_DIR}/*.h
            ${imgui_SOURCE_DIR}/*.cpp

            ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
            )

elseif(UNIX)
    file(GLOB imgui_sources
            ${imgui_SOURCE_DIR}/imgui/*.h
            ${imgui_SOURCE_DIR}/imgui/*.cpp

            ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_android.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_android.cpp
            )

else()
    file(GLOB imgui_sources
            ${imgui_SOURCE_DIR}/imgui/*.h
            ${imgui_SOURCE_DIR}/imgui/*.cpp

            ${imgui_SOURCE_DIR}/backends/imgui_impl_osx.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_osx.mm
            ${imgui_SOURCE_DIR}/backends/imgui_impl_metal.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_metal.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_android.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_android.cpp
            )

endif ()

project(imgui-static)
add_library(imgui-static ${imgui_sources})
target_include_directories(imgui-static PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends ${glfw_SOURCE_DIR}/include ${Vulkan_INCLUDE_DIRS})

#Set folder and group all thirdparty projects

function(get_all_targets var)
    set(targets)
    get_all_targets_recursive(targets ${CMAKE_CURRENT_SOURCE_DIR})
    set(${var} ${targets} PARENT_SCOPE)
endfunction()

macro(get_all_targets_recursive targets dir)
    get_property(subdirectories DIRECTORY ${dir} PROPERTY SUBDIRECTORIES)
    foreach(subdir ${subdirectories})
        get_all_targets_recursive(${targets} ${subdir})
    endforeach()

    get_property(current_targets DIRECTORY ${dir} PROPERTY BUILDSYSTEM_TARGETS)
    list(APPEND ${targets} ${current_targets})
endmacro()

get_all_targets(all_targets)
message("All targets: ${all_targets}")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(${all_targets} PROPERTIES FOLDER thirdparty)