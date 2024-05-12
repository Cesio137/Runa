set(imgui_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(imgui)

file(GLOB imgui_sources
        ${imgui_SOURCE_DIR}/Public/imconfig.h
        ${imgui_SOURCE_DIR}/Public/imgui.h
        ${imgui_SOURCE_DIR}/Private/imgui.cpp
        ${imgui_SOURCE_DIR}/Public/imgui_internal.h
        ${imgui_SOURCE_DIR}/Public/imstb_rectpack.h
        ${imgui_SOURCE_DIR}/Public/imstb_textedit.h
        ${imgui_SOURCE_DIR}/Public/imstb_truetype.h
        ${imgui_SOURCE_DIR}/Private/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/Private/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/Private/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/Private/imgui_widgets.cpp

        ${imgui_SOURCE_DIR}/Public/imgui_impl_sdl2.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_sdl2.cpp
        ${imgui_SOURCE_DIR}/Public/imgui_impl_sdlrenderer2.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_sdlrenderer2.cpp
    )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND  imgui_sources
        ${imgui_SOURCE_DIR}/Public/imgui_impl_win32.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_win32.cpp
        ${imgui_SOURCE_DIR}/Public/imgui_impl_vulkan.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_vulkan.cpp
    )
    if(MSVC)
        list(APPEND  imgui_sources
            ${imgui_SOURCE_DIR}/Public/imgui_impl_dx11.h
            ${imgui_SOURCE_DIR}/Private/imgui_impl_dx11.cpp
            ${imgui_SOURCE_DIR}/Public/imgui_impl_dx12.h
            ${imgui_SOURCE_DIR}/Private/imgui_impl_dx12.cpp
        )
    endif()
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND  imgui_sources 
        ${imgui_SOURCE_DIR}/Public/imgui_impl_vulkan.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_vulkan.cpp
    )
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    list(APPEND  imgui_sources 
        ${imgui_SOURCE_DIR}/Public/imgui_impl_osx.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_osx.mm
        ${imgui_SOURCE_DIR}/Public/imgui_impl_metal.h
        ${imgui_SOURCE_DIR}/Private/imgui_impl_metal.cpp
    )
endif()

add_library(imgui STATIC ${imgui_sources})
target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}/Public" "${imgui_SOURCE_DIR}/Private")
target_link_libraries(imgui
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        Vulkan
)
set_target_properties(imgui PROPERTIES FOLDER "Engine/Source/Thirdparty")


