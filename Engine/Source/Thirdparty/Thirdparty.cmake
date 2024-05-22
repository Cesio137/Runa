set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})
if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    set(TARGET_SYSTEM "Win_")
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    set(TARGET_SYSTEM "Unix_")
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(TARGET_SYSTEM "Darwin_")
endif ()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86_64)|(amd64)|(AMD64)|(x64)")
    set(TARGET_SYSTEM "${TARGET_SYSTEM}x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "(aarch64)|(arm64)|(AARCH64)|(ARM64)")
    set(TARGET_SYSTEM "${TARGET_SYSTEM}arm64")
endif()

# Graphics API
add_subdirectory(${THIRDPARTY_DIR}/Vulkan)
# User Interface
add_subdirectory(${THIRDPARTY_DIR}/imgui)

add_subdirectory(${THIRDPARTY_DIR}/simdjson)
add_subdirectory(${THIRDPARTY_DIR}/Pybind11)

add_subdirectory(${THIRDPARTY_DIR}/asio)