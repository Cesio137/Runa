set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

#VCPKG
find_package(basisu CONFIG REQUIRED)
#find_package(OpenSSL REQUIRED)
find_package(OpenAL CONFIG REQUIRED)
find_package(unofficial-openfbx CONFIG REQUIRED)
find_package(Jolt CONFIG REQUIRED)
find_package(tinyexr CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)

# Dependencies
include(FetchContent)
include(ExternalProject)
set(FETCHCONTENT_QUIET OFF)

#GRAPHICS LIBRARY
add_subdirectory(${THIRDPARTY_DIR}/vulkan)
add_subdirectory(${THIRDPARTY_DIR}/sdl)
add_subdirectory(${THIRDPARTY_DIR}/glad)
add_subdirectory(${THIRDPARTY_DIR}/glm)

#USER INTERFACE LIBRARY
add_subdirectory(${THIRDPARTY_DIR}/imgui)

#SCRIPT LANGUAGE LIBRARY
add_subdirectory(${THIRDPARTY_DIR}/luau)

#NETWORKING/DATA LIBRARY
add_subdirectory(${THIRDPARTY_DIR}/asio)
add_subdirectory(${THIRDPARTY_DIR}/simdjson)

#IMAGE LIBRARY
add_subdirectory(${THIRDPARTY_DIR}/stb)

#PHYSICS LIBRARY
add_subdirectory(${THIRDPARTY_DIR}/box2d)

#STL
add_subdirectory(${THIRDPARTY_DIR}/eastl)