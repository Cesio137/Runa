project(imgui)
set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR})
file(GLOB IMGUI_SOURCES
    *.h 
    *.cpp 
    backends/*.h
    backends/*.cpp
    ) 

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${IMGUI_DIR}/ ${IMGUI_DIR}/backends/)
