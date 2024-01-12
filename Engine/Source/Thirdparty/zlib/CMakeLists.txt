set(ZLIB_DIR ${CMAKE_CURRENT_LIST_DIR}/${TARGET_SYSTEM} CACHE STRING "zlib library dir")

project(zlib)
add_library(zlib INTERFACE)
target_include_directories(zlib
        INTERFACE
        ${ZLIB_DIR}/include
)

if(WIN32)
    target_link_libraries(zlib
            INTERFACE
            ${ZLIB_DIR}/lib/zlib.lib
    )
elseif(UNIX)
    target_link_libraries(zlib
            INTERFACE
            ${ZLIB_DIR}/lib/libz.a
    )
endif()