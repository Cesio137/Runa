set(Nlohmann_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Nlohmann)
file(GLOB_RECURSE Nlohmann_Sources "${Nlohmann_DIR}/Public/*.h")
add_library(Nlohmann INTERFACE ${Nlohmann_Sources})
target_include_directories(Nlohmann
        INTERFACE
        "${Nlohmann_DIR}/Public"
)

set_target_properties(imgui PROPERTIES FOLDER "Engine/Source/Thirdparty")