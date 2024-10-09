find_package(OpenSSL REQUIRED)

add_subdirectory(Config)
add_subdirectory(Source)

target_link_libraries(${CMAKE_PROJECT_NAME}
        RenderInterface
        Network
)