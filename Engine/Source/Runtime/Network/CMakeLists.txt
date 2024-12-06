set(Network_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Network)
file(GLOB_RECURSE Network_Sources "${Network_DIR}/Public/*.hpp")
add_library(Network STATIC ${Network_Sources})
target_include_directories(Network
        PUBLIC
        "${Network_DIR}/Public"
)
target_link_libraries(Network
        PUBLIC
        asio
        PRIVATE
        Config
)

set_target_properties(Network PROPERTIES FOLDER "Engine/Source/Runtime" LINKER_LANGUAGE CXX)

