set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Render_Interface)
add_library(Render_Interface INTERFACE)
target_link_libraries(Render_Interface
        INTERFACE
        SDL2main
        SDL2-static
        glad
        imgui
)

project(Data_Interface)
add_library(Data_Interface INTERFACE)
target_link_libraries(Data_Interface
        INTERFACE
        Data
        boost_locale
)

include(${SOURCE_DIR}/config/config.cmake)
include(${SOURCE_DIR}/data/data.cmake)
include(${SOURCE_DIR}/unicode/unicode.cmake)
include(${SOURCE_DIR}/core/core.cmake)
include(${SOURCE_DIR}/rendering/rendering.cmake)
include(${SOURCE_DIR}/launcher/launcher.cmake)

target_link_libraries(${CMAKE_PROJECT_NAME}
        Core
        Data_Interface
)
