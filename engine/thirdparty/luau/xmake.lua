
package("luau")
    add_deps("cmake")
    set_kind("library")
    set_homepage("https://luau.org/")
    set_description("Luau")
    add_urls("https://github.com/luau-lang/luau.git")
    add_versions("0.681", "0.681")

    on_install(function (package)
        -- Luau configs
        local configs = {
            "-DLUAU_BUILD_CLI=OFF",
            "-DLUAU_BUILD_TESTS=OFF"
        }
        import("package.tools.cmake").build(package, configs)

        local source_dir = path.join(package:builddir(), "..")

        -- Copia includes
        os.trycp(path.join(source_dir, "Analysis", "include"), package:installdir())
        os.trycp(path.join(source_dir, "Ast", "include"), package:installdir())
        os.trycp(path.join(source_dir, "CLI", "include"), package:installdir())
        os.trycp(path.join(source_dir, "CodeGen", "include"), package:installdir())
        os.trycp(path.join(source_dir, "Common", "include"), package:installdir())
        os.trycp(path.join(source_dir, "Compiler", "include"), package:installdir())
        os.trycp(path.join(source_dir, "Config", "include"), package:installdir())
        os.trycp(path.join(source_dir, "EqSat", "include"), package:installdir())
        os.trycp(path.join(source_dir, "VM", "include"), package:installdir())
        os.trycp(path.join(source_dir, "Require", "Navigator", "include"), package:installdir())
        os.trycp(path.join(source_dir, "Require", "Runtime", "include"), package:installdir())

        -- Copy libs
        os.trycp(path.join(package:builddir(), "**.a"), package:installdir("lib"))
        os.trycp(path.join(package:builddir(), "**.so"), package:installdir("lib"))
        os.trycp(path.join(package:builddir(), "**.dylib"), package:installdir("lib"))
        os.trycp(path.join(package:builddir(), "**.lib"), package:installdir("lib"))
        os.trycp(path.join(package:builddir(), "**.dll"), package:installdir("bin"))
        
        -- Fix Luau.CLI.lib.lib name
        os.trymv(path.join(package:installdir("lib"), "Luau.CLI.lib.lib"), path.join(package:installdir("lib"), "Luau.CLI.lib"))
        os.trycp(path.join(package:installdir("lib"), "libLuau.CLI.lib.a"), path.join(package:installdir("lib"), "Luau.CLI.a"))
    end)
package_end()

add_requires("luau")