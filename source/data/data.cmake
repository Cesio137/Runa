set(Data_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Data)
file(GLOB_RECURSE Data_Sources "${Data_DIR}/public/*.h")
add_library(Data STATIC ${Data_Sources})
target_include_directories(Data
        PUBLIC
        "${Data_DIR}/public/config"
        "${Data_DIR}/public/struct"
        "${Data_DIR}/public/enum"
        "${Data_DIR}/public/type"
        INTERFACE
        "${Data_DIR}/public/config"
        "${Data_DIR}/public/struct"
        "${Data_DIR}/public/enum"
        "${Data_DIR}/public/type"
)
target_link_libraries(Data
        Qt${QT_VERSION_MAJOR}::Core
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(ENGINE_BUILD_DEBUG ON)
else()   
        set(ENGINE_BUILD_RELEASE ON)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(ENGINE_BUILD_DEBUG ON)
else()
        set(ENGINE_BUILD_RELEASE ON)
endif()

set(C_COMPILER_ID ${CMAKE_C_COMPILER_ID})
set(CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID})

set(ENGINE_NAME ${CMAKE_PROJECT_NAME})
set(ENGINE_VERSION ${CMAKE_PROJECT_VERSION})

if (DEFINED CMAKE_PROJECT_VERSION_MAJOR)
        set(ENGINE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
else()   
        set(ENGINE_VERSION_MAJOR ON)
endif()

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(HOST_SYSTEM_WINDOWS ON)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        set(HOST_SYSTEM_LINUX ON)
elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
        set(HOST_SYSTEM_DARWIN ON)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(TARGET_SYSTEM_WINDOWS ON)
elseif(TARGET_SYSTEM_NAME STREQUAL "Linux")
        set(TARGET_SYSTEM_LINUX ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(TARGET_SYSTEM_DARWIN ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Android")
        set(TARGET_SYSTEM_ANDROID ON)
elseif (CMAKE_SYSTEM_NAME STREQUAL "iOS")
        set(TARGET_SYSTEM_IOS ON)
endif()

if (DEFINED CMAKE_PROJECT_VERSION_PATCH)
        set(ENGINE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
else()   
        set(ENGINE_VERSION_PATCH 0)
endif()

set(DICTIONARY_PATH ${CMAKE_SOURCE_DIR}/doc/lang/)

configure_file(${Data_DIR}/public/config/Config.h.in ${Data_DIR}/public/config/Config.h @ONLY)