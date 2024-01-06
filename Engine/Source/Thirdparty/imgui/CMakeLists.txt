set(imgui_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(imgui)

file(GLOB imgui_sources
        ${imgui_SOURCE_DIR}/*.h
        ${imgui_SOURCE_DIR}/*.cpp
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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND  imgui_sources
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_win32.cpp
    )
    if(MSVC)
        list(APPEND  imgui_sources 
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx9.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx10.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx11.cpp
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.h
            ${imgui_SOURCE_DIR}/backends/imgui_impl_dx12.cpp
        )
    endif()
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    list(APPEND  imgui_sources 
        ${imgui_SOURCE_DIR}/backends/imgui_impl_osx.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_osx.mm
        ${imgui_SOURCE_DIR}/backends/imgui_impl_metal.h
        ${imgui_SOURCE_DIR}/backends/imgui_impl_metal.cpp
    )
endif()


add_library(imgui STATIC ${imgui_sources})
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(imgui
        PRIVATE
        SDL2
        ${Vulkan_LIBRARIES}
)
set_target_properties(imgui PROPERTIES FOLDER Thirdparty)


