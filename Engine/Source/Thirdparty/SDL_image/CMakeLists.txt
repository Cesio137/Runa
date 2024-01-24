set(SDLIMAGE_DIR ${CMAKE_CURRENT_LIST_DIR}/${TARGET_SYSTEM})

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
