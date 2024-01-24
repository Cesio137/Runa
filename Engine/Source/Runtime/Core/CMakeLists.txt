set(Core_DIR ${CMAKE_CURRENT_LIST_DIR})

project(Core)
file(GLOB_RECURSE Core_Sources "${Core_DIR}/include/*.h" "${Core_DIR}/src/*.cpp")
add_library(Core STATIC ${Core_Sources})
target_include_directories(Core
        PUBLIC
        "${Core_DIR}/include"
)
target_link_libraries(Core
        PUBLIC
        Nlohmann
)

add_custom_command(TARGET Core POST_BUILD
        COMMAND  ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:Core> ${RUNTIME_OUTPUT_DIRECTORY}/Engine/Source/Runtime/Core/lib
)

set_target_properties(Core PROPERTIES FOLDER "Engine/Source/Runtime")
set_target_properties( Core
        PROPERTIES
        #ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Engine/Source/Runtime/Core/lib"
        #RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)