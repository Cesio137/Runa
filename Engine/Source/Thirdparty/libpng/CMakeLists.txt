if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(amd64)|(AMD64)")

    if(WIN32)
        set(LIBPNG_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_x64)
    elseif(UNIX)
        set(LIBPNG_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_x64)
    endif()
    
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(aarch64)|(arm64)|(AARCH64)|(ARM64)")

    if(WIN32)
        set(LIBPNG_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_arm64)
    elseif(UNIX)
        set(LIBPNG_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_arm64)
    endif()

endif()

project(libpng)
add_library(libpng INTERFACE)
target_include_directories(libpng
        INTERFACE
    ${LIBPNG_DIR}/include
)

if(WIN32)
    target_link_libraries(libpng
            INTERFACE
            ${LIBPNG_DIR}/lib/libpng16_static.lib
            ${LIBPNG_DIR}/lib/png.lib
    )
elseif(UNIX)
    target_link_libraries(libpng
            INTERFACE
            ${LIBPNG_DIR}/lib/libpng16.a
            ${LIBPNG_DIR}/lib/libpng.a
    )
endif()