target("stc")
    set_group("engine/thirdparty")
    set_kind("static")
    add_defines(
        "STC_CSTR_CORE"
    )
    add_includedirs("include", {public = true})
    add_headerfiles("include/**.h")
    add_files("src/*.c")