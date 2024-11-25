set_languages("c++17")

target("0")
do
	set_kind(binary)
	add_files("*.cpp", "tests/0.cpp")
end

target("1")
do
	set_kind(binary)
	add_files("*.cpp", "tests/1.cpp")
end
