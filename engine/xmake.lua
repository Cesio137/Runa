
-- Setup thirdparty libraries
includes(
    "thirdparty/vulkan",
    "thirdparty/glad",
    "thirdparty/sdl3",
    "thirdparty/imgui",
    "thirdparty/luau",
    "thirdparty/glm",
    "thirdparty/stb",
    "thirdparty/stc",
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
        "stc",
        "simdjson",
        "asio"
    )

target("Runa")
    set_group("engine")
    set_kind("binary")
    add_includedirs("runa/include")
    add_headerfiles("runa/include/**.h")
    add_files("runa/src/**.cpp")
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
         "stc",
         "simdjson",
         "asio"
    )
    after_build(function (target)
        os.cp(path.absolute("content/resources"), path.join(target:targetdir(), "resources"))
    end)