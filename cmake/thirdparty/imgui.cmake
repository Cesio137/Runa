if(NOT Vulkan_FOUND)
    include(thirdparty/vulkan.cmake)
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
