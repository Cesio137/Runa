set(PYBIND11_DIR ${CMAKE_CURRENT_LIST_DIR})


project(Pybind11)
add_library(Pybind11 INTERFACE)
target_include_directories(Pybind11
        INTERFACE
        ${PYBIND11_DIR}/include
)