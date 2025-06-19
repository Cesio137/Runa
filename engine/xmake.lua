
-- Setup thirdparty libraries
includes(
    "thirdparty/vulkan",
    "thirdparty/glad",
    "thirdparty/sdl3",
    "thirdparty/imgui",
    "thirdparty/luau",
    "thirdparty/glm",
    "thirdparty/stb",
    "thirdparty/simdjson",
    "thirdparty/asio"
)

-- Setup engine source files
target("Runtime")
    set_group("engine")
    set_kind("static")
    add_defines(
        "STB_IMAGE_IMPLEMENTATION"
    )
    add_includedirs("runtime/include", {public = true})
    add_headerfiles("runtime/include/**.h")
    add_files("runtime/src/**.c")
    add_packages(
        "libsdl3",
        "glm",
        "imgui",
        "luau"
    )
    add_deps(
        "vulkan",
        "glad",
        "stb",
        "simdjson",
        "asio"
    )

target("Editor")
    set_group("editor")
    set_kind("binary")
    add_defines(
        "STB_IMAGE_IMPLEMENTATION"
    )
    add_includedirs("editor/include")
    add_headerfiles("editor/include/**.h")
    add_files("editor/src/**.cpp")
    add_packages(
        "libsdl3",
        "glm",
        "imgui",
        "luau"
    )
    add_deps(
         "Runtime",
         "vulkan",
         "glad",
         "stb",
         "simdjson",
         "asio"
    )