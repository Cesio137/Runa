cmake_minimum_required(VERSION 3.22)

project(Lumen LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

set(TS_FILES Lumen_en_001.ts)

add_executable(${CMAKE_PROJECT_NAME}
  Source/main.cpp
  ${TS_FILES}
)

include(config.cmake)

target_link_libraries(${CMAKE_PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    Engine
    Rendering
    glfw
    glad
    imgui-static
    #[[
    Rendering
    bgfx
    bx
    glfw
    glad
    imgui-static
    Bullet3Dynamics
    Bullet3Collision
    BulletSoftBody
    LinearMath
    OpenCL
    ]]
)

if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

install(TARGETS Lumen
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})