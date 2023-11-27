set(Nlohmann_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Nlohmann)
file(GLOB_RECURSE Nlohmann_Sources "${Nlohmann_DIR}/*.h")
add_library(Nlohmann INTERFACE ${Nlohmann_Sources})
target_include_directories(Nlohmann
        INTERFACE
        "${Nlohmann_DIR}/include"
)

set_target_properties(Nlohmann PROPERTIES FOLDER "Thirdparty")