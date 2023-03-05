FetchContent_GetProperties(opencl)
if(NOT opencl_POPULATED)
    FetchContent_Declare(
            opencl
            GIT_REPOSITORY https://github.com/KhronosGroup/OpenCL-SDK.git
            GIT_TAG        81ebd78c33680960c5a4edf9509e2107b6204534 # 2022.09.30
    )

    FetchContent_MakeAvailable(opencl)
    #add_subdirectory(${opencl_SOURCE_DIR})
endif()