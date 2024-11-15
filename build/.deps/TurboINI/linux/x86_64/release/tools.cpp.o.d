{
    files = {
        "tools.cpp"
    },
    depfiles_gcc = "tools.o: tools.cpp tools.hpp\
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