add_rules("mode.debug", "mode.release")
add_languages("c++23")

target("TurboINI")
    set_kind("static")
    add_files("parser.cpp",
              "tools.cpp")
