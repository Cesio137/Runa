set(IMGUI_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(imgui)

set(IMGUI_SOURCES
        ${IMGUI_SOURCE_DIR}/include/imconfig.h
        ${IMGUI_SOURCE_DIR}/include/imgui.h
        ${IMGUI_SOURCE_DIR}/src/imgui.cpp
        ${IMGUI_SOURCE_DIR}/include/imgui_internal.h
        ${IMGUI_SOURCE_DIR}/include/imstb_rectpack.h
        ${IMGUI_SOURCE_DIR}/include/imstb_textedit.h
        ${IMGUI_SOURCE_DIR}/include/imstb_truetype.h
        ${IMGUI_SOURCE_DIR}/src/imgui_demo.cpp
        ${IMGUI_SOURCE_DIR}/src/imgui_draw.cpp
        ${IMGUI_SOURCE_DIR}/src/imgui_tables.cpp
        ${IMGUI_SOURCE_DIR}/src/imgui_widgets.cpp

        ${IMGUI_SOURCE_DIR}/include/imgui_impl_sdl3.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_sdl3.cpp
        ${IMGUI_SOURCE_DIR}/include/imgui_impl_sdlrenderer3.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_sdlrenderer3.cpp
    )

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    list(APPEND  IMGUI_SOURCES
        ${IMGUI_SOURCE_DIR}/include/imgui_impl_win32.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_win32.cpp
        ${IMGUI_SOURCE_DIR}/include/imgui_impl_vulkan.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_vulkan.cpp
    )
    if(MSVC)
        list(APPEND  IMGUI_SOURCES
            ${IMGUI_SOURCE_DIR}/include/imgui_impl_dx11.h
            ${IMGUI_SOURCE_DIR}/src/imgui_impl_dx11.cpp
            ${IMGUI_SOURCE_DIR}/include/imgui_impl_dx12.h
            ${IMGUI_SOURCE_DIR}/src/imgui_impl_dx12.cpp
        )
    endif()
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND  IMGUI_SOURCES 
        ${IMGUI_SOURCE_DIR}/include/imgui_impl_vulkan.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_vulkan.cpp
    )
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    list(APPEND  IMGUI_SOURCES 
        ${IMGUI_SOURCE_DIR}/include/imgui_impl_osx.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_osx.mm
        ${IMGUI_SOURCE_DIR}/include/imgui_impl_metal.h
        ${IMGUI_SOURCE_DIR}/src/imgui_impl_metal.cpp
    )
endif()

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "${IMGUI_SOURCE_DIR}/include")
target_link_libraries(imgui
        PUBLIC
        SDL3-static
        vulkan
)


