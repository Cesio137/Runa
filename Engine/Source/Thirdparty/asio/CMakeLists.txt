set(Asio_DIR ${CMAKE_CURRENT_LIST_DIR})

project(asio)
file(GLOB_RECURSE Asio_Sources "${Asio_DIR}/Public/*.h")
add_library(asio INTERFACE ${Asio_Sources})
target_include_directories(asio
        INTERFACE
        "${Asio_DIR}/Public"
)

set_target_properties(asio PROPERTIES FOLDER "Engine/Source/Thirdparty")