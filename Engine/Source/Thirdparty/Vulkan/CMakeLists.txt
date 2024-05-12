set(VULKAN_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Vulkan)
file(GLOB_RECURSE VULKAN_Sources "${VULKAN_DIR}/Public/*.h")
add_library(Vulkan INTERFACE ${VULKAN_Sources})
target_include_directories(Vulkan
        INTERFACE
        "${VULKAN_DIR}/Public"
)