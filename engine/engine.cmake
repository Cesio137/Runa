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
        #GRAPHICS LIBRARY
        SDL3::SDL3-static
        glad
        glm
        #USER INTERFACE LIBRARY
        imgui
        #SCRIPT LANGUAGE LIBRARY
        Luau.VM
        Luau.Compiler
        #CRYPTO LIBRARY
        
        #NETWORKING/DATA LIBRARY
        asio
        simdjson
        #COMPRESSION LIBRARY
        zstd::libzstd
        #IMAGE LIBRARY
        stb
        unofficial::tinyexr::tinyexr
        basisu::basisu_encoder
        #MEDIA LIBRARY
        OpenAL::OpenAL
        #PHYSICS LIBRARY
        Jolt::Jolt
        box2d::box2d
        #OBJ LIBRARY
        unoffical::openfbx::openfbx
        #STL
        EASTL
)