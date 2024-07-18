-- set minimum xmake version
set_xmakever("2.8.2")

-- add custom package repository
add_repositories("re https://github.com/Starfield-Reverse-Engineering/commonlibsf-xrepo")
-- import changed commonlibsf plugin rule , this rule don't create plugin.cpp
includes("commonlibsf_plugin_without_plugin_cpp.lua")

-- set project
set_project("AlwaysLockSomeAbilityAfterPerk")
set_version("0.0.0")
set_license("GPL-3.0")

-- set defaults
set_languages("c++23")
set_optimize("faster")
set_warnings("allextra", "error")
set_defaultmode("releasedbg")

-- add rules
add_rules("mode.releasedbg", "mode.debug")
add_rules("plugin.vsxmake.autoupdate")

-- require package dependencies
add_requires("commonlibsf")
add_requires("simpleini")

-- setup targets
target("AlwaysLockSomeAbilityAfterPerk")
    -- bind package dependencies
    add_packages("commonlibsf")
    add_packages("simpleini")
    -- add commonlibsf plugin
    add_rules("commonlibsf_plugin_without_plugin_cpp", {
        author = "typeryougishiki",
        description = "",
        email = "typeryougishiki@163.com"
    })
    -- add source files
    set_pcxxheader("src/pch.h")
    add_headerfiles("src/pch/*.h")
    local add_dir_as_source_and_include = function(path)
        add_files(path.."/*.cpp")
        add_headerfiles(path.."/*.h")
        add_includedirs(path)
    end
    add_dir_as_source_and_include("src")
    add_dir_as_source_and_include("src/utils")
    add_dir_as_source_and_include("src/hook")
