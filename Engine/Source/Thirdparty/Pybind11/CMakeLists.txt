set(Pybind11_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Pybind11)
file(GLOB_RECURSE Pybind11_Sources "${Pybind11_DIR}/Public/*.h")
add_library(Pybind11 INTERFACE ${Pybind11_Sources})
target_include_directories(Pybind11
        INTERFACE
        "${Pybind11_DIR}/Public"
)

set_target_properties(Pybind11 PROPERTIES FOLDER "Engine/Source/Thirdparty")