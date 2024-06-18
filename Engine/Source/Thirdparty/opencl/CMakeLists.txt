set(OPENCL_DIR ${CMAKE_CURRENT_LIST_DIR})

project(OpenCL)
file(GLOB_RECURSE OpenCL_Sources "${OPENCL_DIR}/Public/*.h")
add_library(OpenCL INTERFACE ${OpenCL_Sources})
target_include_directories(OpenCL
        INTERFACE
        "${OPENCL_DIR}/Public"
)

set_target_properties(OpenCL PROPERTIES FOLDER "Engine/Source/Thirdparty")