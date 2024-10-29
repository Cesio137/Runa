set(Config_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Config)
file(GLOB_RECURSE Config_Sources "${Config_DIR}/*.h")
add_library(Config INTERFACE ${Config_Sources})
target_include_directories(Config
        INTERFACE
        "${Config_DIR}"
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ENGINE_BUILD_DEBUG ON)
else()
    set(ENGINE_BUILD_RELEASE ON)
endif()

set(ENGINE_NAME ${CMAKE_PROJECT_NAME})
set(ENGINE_VERSION ${CMAKE_PROJECT_VERSION})
set(ENGINE_MAJOR_VERSION ${CMAKE_PROJECT_VERSION_MAJOR})
set(ENGINE_MINOR_VERSION ${CMAKE_PROJECT_VERSION_MINOR})
set(ENGINE_PATH_VERSION ${CMAKE_PROJECT_VERSION_PATCH})

configure_file(${Config_DIR}/Config.h.in ${Config_DIR}/Config.h @ONLY)

set_target_properties(Config PROPERTIES FOLDER "Engine")