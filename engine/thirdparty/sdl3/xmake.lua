-- Enable "fetch" support
add_rules("plugin.fetch")

-- Fetch from github
--[[
package("sdl3")
    add_deps("cmake")
    
    set_kind("library")
    set_homepage("https://github.com/libsdl-org/SDL")
    set_description("Simple DirectMedia Layer")
    add_urls("https://github.com/libsdl-org/SDL.git")
    add_versions("release-3.2.16", "6340e58879b2d15830c8460d2f589a385c444d1faa2a4828a9626c7322562be8")

    on_install(function (package)
        -- SDL3 configs
        sdl_config = {
            "-DSDL_TEST=OFF",
            "-DSDL_STATIC=ON",
            "-DSDL_SHARED=ON"
        }

        if is_plat("linux") then
            table.insert(sdl_config, "-DSDL_X11=OFF")
            table.insert(sdl_config, "-DSDL_JACK_SHARED=OFF")
            table.insert(sdl_config, "-DSDL_SNDIO_SHARED=OFF")
            table.insert(sdl_config, "-DSDL_KMSDRM_SHARED=OFF")
            table.insert(sdl_config, "-DSDL_HIDAPI_LIBUSB_SHARED=OFF")
            table.insert(sdl_config, "-DSDL_WAYLAND_LIBDECOR_SHARED=ON")
            table.insert(sdl_config, "-DSDL_ALSA_SHARED=ON")
            table.insert(sdl_config, "-DSDL_PIPEWIRE_SHARED=ON")
            table.insert(sdl_config, "-DSDL_PULSEAUDIO_SHARED=OFF")
            table.insert(sdl_config, "-DSDL_WAYLAND_SHARED=ON")
        end
        import("package.tools.cmake").install(package, sdl_config)
    end)

    on_test(function (package)
        assert(package:has_cfuncs("SDL_InitSubSystem", {includes = "SDL3/SDL.h"}))
    end)
package_end()
]]
-- Requere SDL3 como dependência
-- add_requires("sdl3", {alias = "SDL3", configs = {shared = true , debug = is_mode("debug")}})
add_requires("libsdl3")
