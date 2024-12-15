set(THIRDPARTY_DIR ${CMAKE_CURRENT_LIST_DIR})

# Dependencies
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

add_subdirectory(${THIRDPARTY_DIR}/asio)
add_subdirectory(${THIRDPARTY_DIR}/simdjson)
add_subdirectory(${THIRDPARTY_DIR}/sdl3)
add_subdirectory(${THIRDPARTY_DIR}/vulkan)
add_subdirectory(${THIRDPARTY_DIR}/imgui)
add_subdirectory(${THIRDPARTY_DIR}/lua)
add_subdirectory(${THIRDPARTY_DIR}/sol)
