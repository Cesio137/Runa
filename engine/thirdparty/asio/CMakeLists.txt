set(ASIO_DIR ${CMAKE_CURRENT_LIST_DIR})

project(asio)
file(GLOB_RECURSE Asio_Sources "${ASIO_DIR}/include/*.h")
add_library(asio INTERFACE ${Asio_Sources})
target_include_directories(asio
        INTERFACE
        "${ASIO_DIR}/include"
)
target_link_libraries(asio
        INTERFACE
        $<TARGET_NAME_IF_EXISTS:OpenSSL::SSL>
        $<TARGET_NAME_IF_EXISTS:OpenSSL::Crypto>
)
