add_rules("mode.release", "mode.debug")
set_languages("c++17")

TurboINIStaticLibraryPath = "build/" .. os.host() .. "/" .. os.arch() .. "/release/"

target("TurboINI")
do
	set_default(true)
	set_kind("static")
	add_files("*.cpp")
end

target("TurboINITest0")
do
    set_default(false)
	set_kind("binary")
	add_linkdirs(TurboINIStaticLibraryPath)
	add_links("TurboINI")
	add_includedirs(".")
	add_files("tests/0.cpp")
end
