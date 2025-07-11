target("stb")
    set_group("engine/thirdparty")
    set_kind("static")
    add_defines(
        "STB_IMAGE_IMPLEMENTATION"
    )
    add_includedirs("include", {public = true})
    add_headerfiles("include/*.h")
    add_files("src/*.c")