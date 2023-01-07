set(VULKAN_DIR ${CMAKE_CURRENT_LIST_DIR})

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    message(STATUS "Vulkan target include directories: ${Vulkan_INCLUDE_DIRS}")
    target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${Vulkan_INCLUDE_DIRS})
    message(STATUS "Vulkan libraries directories: ${Vulkan_LIBRARY}")
    target_link_libraries(${CMAKE_PROJECT_NAME} ${Vulkan_LIBRARY})

else()
    message(FATAL_ERROR "You have to install vulkan sdk from 'https://vulkan.lunarg.com/sdk/home'.")
    
endif(Vulkan_FOUND)


#file(GLOB files "${Vulkan_INCLUDE_DIRS}/../Lib/*.lib")
#foreach(file ${files})
  #... calculate ${i} to get the test name
  #add_test(validate_${i}, "validator", ${file})
  #message(STATUS ${file})
#endforeach()
