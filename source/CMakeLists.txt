set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${SOURCE_DIR}/data/data.cmake)
include(${SOURCE_DIR}/runtime/runtime.cmake)
include(${SOURCE_DIR}/coreapplication/coreapplication.cmake)
include(${SOURCE_DIR}/launcher/launcher.cmake)
include(${SOURCE_DIR}/rendering/rendering.cmake)

project(Render_Interface)
add_library(Render_Interface INTERFACE)
target_link_libraries(Render_Interface
        INTERFACE
        SDL2main
        SDL2
        glad-static
        imgui-static
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        CoreApplication
)