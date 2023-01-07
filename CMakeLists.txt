cmake_minimum_required(VERSION 3.20)

project(Lumen LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core LinguistTools)

set(TS_FILES Lumen_pt_BR.ts)
add_executable(${CMAKE_PROJECT_NAME} 
                main.cpp
                ${TS_FILES}
              )

# Add sources and libraries to project
add_subdirectory(engine)
add_subdirectory(thirdparty)

#link static libraries
target_link_libraries(Lumen Qt${QT_VERSION_MAJOR}::Core imgui glfw glad SDL2-static)

#Create QT translate files
if(COMMAND qt_create_translation)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

install(TARGETS Lumen
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

#Post build commands
include(build.config.cmake)