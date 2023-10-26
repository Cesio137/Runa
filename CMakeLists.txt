cmake_minimum_required(VERSION 3.24)

project(Nanometro LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

add_executable(Nanometro
  source/main.cpp
)
include(config.cmake)
target_link_libraries(Nanometro
        Qt${QT_VERSION_MAJOR}::Core
)

include(GNUInstallDirs)
install(TARGETS Nanometro
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
