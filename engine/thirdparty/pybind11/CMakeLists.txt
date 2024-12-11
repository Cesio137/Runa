set(PYBIND11_DIR ${CMAKE_CURRENT_LIST_DIR})

project(pybind11)
file(GLOB_RECURSE PYBIND11_SOURCES "${PYBIND11_DIR}/include/*.h")
add_library(pybind11 INTERFACE ${Pybind11_Sources})
target_include_directories(pybind11
        INTERFACE
        "${PYBIND11_DIR}/include"
)