set(ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR})

include(${ENGINE_DIR}/thirdparty/thirdparty.cmake)

add_subdirectory(${ENGINE_DIR}/config)
add_subdirectory(${ENGINE_DIR}/include)
add_subdirectory(${ENGINE_DIR}/src)

add_executable(${CMAKE_PROJECT_NAME} ${RUNA_HEADERS} ${RUNA_SOURCES})

target_include_directories(${CMAKE_PROJECT_NAME} 
    PUBLIC
    ${ENGINE_DIR}/include
)

target_link_libraries(${CMAKE_PROJECT_NAME} 
    PUBLIC
    config
    SDL3-static
    imgui
    asio
)