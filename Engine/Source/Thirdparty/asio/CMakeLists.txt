set(Asio_DIR ${CMAKE_CURRENT_LIST_DIR})

project(asio)
file(GLOB_RECURSE Asio_Sources "${Asio_DIR}/Public/*.h")
add_library(asio INTERFACE ${Asio_Sources})
target_include_directories(asio
        INTERFACE
        "${Asio_DIR}/Public"
)
target_link_libraries(asio
        INTERFACE
        $<TARGET_NAME_IF_EXISTS:OpenSSL::SSL>
        $<TARGET_NAME_IF_EXISTS:OpenSSL::Crypto>
)
set_target_properties(asio PROPERTIES FOLDER "Engine/Source/Thirdparty")