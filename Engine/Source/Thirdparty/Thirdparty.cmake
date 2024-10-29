set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

# Graphics API
add_subdirectory(${THIRDPARTY_DIR}/vulkan)
add_subdirectory(${THIRDPARTY_DIR}/opencl)
# User Interface
add_subdirectory(${THIRDPARTY_DIR}/imgui)

add_subdirectory(${THIRDPARTY_DIR}/simdjson)
add_subdirectory(${THIRDPARTY_DIR}/pybind11)

add_subdirectory(${THIRDPARTY_DIR}/asio)