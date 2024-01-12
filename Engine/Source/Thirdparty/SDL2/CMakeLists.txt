set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/${TARGET_SYSTEM})


project(SDL2)
add_library(SDL2 INTERFACE)
target_include_directories(SDL2
        INTERFACE
        ${SDL2_DIR}/include/SDL2
)

if(WIN32)
    target_link_libraries(SDL2
            INTERFACE
            ${SDL2_DIR}/lib/SDL2.lib
            ${SDL2_DIR}/lib/SDL2main.lib
    )
    set(SDL2_SHARE_LIBRARY ${SDL2_DIR}/bin/SDL2.dll CACHE STRING "sdl2 dynamic link file")
elseif(UNIX)
    target_link_libraries(SDL2
            INTERFACE
            ${SDL2_DIR}/lib/libSDL2.so
            ${SDL2_DIR}/lib/libSDL2main.a
    )
    set(SDL2_SHARE_LIBRARY ${SDL2_DIR}/lib/libSDL2.so CACHE STRING "sdl2 dynamic link file")
endif()