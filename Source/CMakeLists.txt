set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${SOURCE_DIR}/data/data.cmake)
include(${SOURCE_DIR}/core/core.cmake)
include(${SOURCE_DIR}/rendering/rendering.cmake)
include(${SOURCE_DIR}/launcher/launcher.cmake)

target_link_libraries(Nanometro
        Core
)