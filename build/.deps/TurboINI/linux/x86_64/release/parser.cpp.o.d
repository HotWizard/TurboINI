{
    files = {
        "parser.cpp"
    },
    depfiles_gcc = "parser.o: parser.cpp parser.hpp tools.hpp\
",
    values = {
        "/usr/bin/gcc",
        {
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-O3",
            "-std=c++23",
            "-DNDEBUG"
        }
    }
}