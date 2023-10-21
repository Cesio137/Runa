set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Source_Interface)
add_library(Source_Interface INTERFACE)
target_link_libraries(Source_Interface
        INTERFACE
        Data
        SDL2main
        SDL2-static
        glad
        imgui
)

include(${SOURCE_DIR}/config/config.cmake)
include(${SOURCE_DIR}/data/data.cmake)
include(${SOURCE_DIR}/unicode/unicode.cmake)
include(${SOURCE_DIR}/core/core.cmake)
include(${SOURCE_DIR}/rendering/rendering.cmake)
include(${SOURCE_DIR}/launcher/launcher.cmake)

target_link_libraries(Nanometro
        Core
)
