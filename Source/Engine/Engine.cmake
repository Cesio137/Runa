set(Engine_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Engine)
file(GLOB_RECURSE Engine_Sources "*.h" "*.cpp")
add_library(Engine STATIC ${Engine_Sources})
target_include_directories(Engine
        PUBLIC
        "${Engine_DIR}/Public"
        PRIVATE
        "${Engine_DIR}/Private"
        INTERFACE
        "${Engine_DIR}/Private"
        )
target_link_libraries(Engine
        PRIVATE
        Source_Interface
        )