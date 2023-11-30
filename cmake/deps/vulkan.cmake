find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Vulkan target include directories: ${Vulkan_INCLUDE_DIRS}")
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
    message(STATUS "Vulkan libraries directories: ${Vulkan_LIBRARIES}")
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Vulkan_LIBRARIES})

else()
    message(FATAL_ERROR "You have to install vulkan sdk from 'https://vulkan.lunarg.com/sdk/home'.")

endif()