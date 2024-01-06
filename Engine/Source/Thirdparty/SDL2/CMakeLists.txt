if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(amd64)|(AMD64)")

    if(WIN32)
        set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_x64 CACHE STRING "sdl2 library dir")
    elseif(UNIX)
        set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_x64 CACHE STRING "sdl2 library dir")
    endif()
    
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(aarch64)|(arm64)|(AARCH64)|(ARM64)")

    if(WIN32)
        set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_arm64 CACHE STRING "sdl2 library dir")
    elseif(UNIX)
        set(SDL2_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_arm64 CACHE STRING "sdl2 library dir")
    endif()

endif()

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
elseif(UNIX)
    target_link_libraries(SDL2
            INTERFACE
            ${SDL2_DIR}/lib/libSDL2.so
            ${SDL2_DIR}/lib/libSDL2main.a
    )
endif()
