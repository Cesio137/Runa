if(NOT Vulkan_FOUND)
    include(deps/vulkan.cmake)
endif()

FetchContent_GetProperties(sdl2)
if(NOT sdl2_POPULATED)
    include(fetch/sdl2.cmake)
endif()

FetchContent_GetProperties(imgui)
if(NOT imgui_POPULATED)
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.89.9-docking # 1.89.9 docking
        GIT_PROGRESS TRUE
      )
  
    FetchContent_MakeAvailable(imgui)
    #add_subdirectory(${imgui_SOURCE_DIR} ${imgui_BINARY_DIR})

    if (WIN32)
        file(GLOB imgui_sources
                ${imgui_SOURCE_DIR}/*.h
                ${imgui_SOURCE_DIR}/*.cpp

                ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
                if(MSVC)
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp
                endif(MSVC)
                if(Vulkan_FOUND)
                ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
                endif(Vulkan_FOUND)
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.cpp
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
                if(Vulkan_FOUND)
                ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_vulkan.cpp
                endif(Vulkan_FOUND)
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
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
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl2.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_sdlrenderer.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.h
                ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl2.cpp
                )

    endif ()

    project(imgui)
    add_library(imgui STATIC ${imgui_sources})
    target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends PRIVATE ${sdl2_SOURCE_DIR}/include ${Vulkan_INCLUDE_DIRS})
endif()


