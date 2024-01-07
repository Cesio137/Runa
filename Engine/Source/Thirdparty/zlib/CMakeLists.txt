if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(amd64)|(AMD64)")

    if(WIN32)
        set(ZLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_x64 CACHE STRING "zlib library dir")
    elseif(UNIX)
        set(ZLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_x64 CACHE STRING "zlib library dir")
    endif()
    
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(aarch64)|(arm64)|(AARCH64)|(ARM64)")

    if(WIN32)
        set(ZLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/Win_arm64 CACHE STRING "zlib library dir")
    elseif(UNIX)
        set(ZLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/Unix_arm64 CACHE STRING "zlib library dir")
    endif()

endif()

project(zlib)
add_library(zlib INTERFACE)
target_include_directories(zlib
        INTERFACE
        ${ZLIB_DIR}/include
)

if(WIN32)
    target_link_libraries(zlib
            INTERFACE
            ${ZLIB_DIR}/lib/zlibstatic.lib
    )
elseif(UNIX)
    target_link_libraries(zlib
            INTERFACE
            ${ZLIB_DIR}/lib/libz.a
    )
endif()