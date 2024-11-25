set_languages("c++17")

add_files("*.cpp")

target("0")
do
	add_files("tests/0.cpp")
end

target("1")
do
	add_files("tests/1.cpp")
end

target("2")
do
	add_files("tests/2.cpp")
end
