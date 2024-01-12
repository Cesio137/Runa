set(VULKAN_DIR ${CMAKE_CURRENT_LIST_DIR})


project(Vulkan)
add_library(Vulkan INTERFACE)
target_include_directories(Vulkan
        INTERFACE
        ${VULKAN_DIR}/include
)