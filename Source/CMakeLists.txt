set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${SOURCE_DIR}/rendering/rendering.cmake)
include(${SOURCE_DIR}/launcher/launcher.cmake)

target_link_libraries(Nanometro
        Qt${QT_VERSION_MAJOR}::Core
        Launcher
        Rendering
)