if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(amd64)|(AMD64)")

    if(WIN32)
        set(SDLIMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_x64)
    elseif(UNIX)
        set(SDLIMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_x64)
    endif()
    
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(aarch64)|(arm64)|(AARCH64)|(ARM64)")

    if(WIN32)
        set(SDLIMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_arm64)
    elseif(UNIX)
        set(SDLIMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_arm64)
    endif()

endif()

project(SDL_image)
add_library(SDL_image INTERFACE)
target_include_directories(SDL_image
    INTERFACE
    ${SDLIMAGE_DIR}/include/SDL2
)

if(WIN32)
    target_link_libraries(SDL_image
            INTERFACE
            ${SDLIMAGE_DIR}/lib/SDL_image-static.lib
    )
elseif(UNIX)
    target_link_libraries(SDL_image
            INTERFACE
            ${SDLIMAGE_DIR}/lib/libSDL2_image.a
    )
endif()