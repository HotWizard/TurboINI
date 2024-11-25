#include "../TurboINI.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

inline auto parser = std::make_unique<TurboINI::parser>();

const inline void CreateINIFile()
{
    auto os = std::make_unique<std::ofstream>("ini.ini");

    *os << "\"integer\"=-0123456789\n"
           "\"string\"=\"value\"\n\n"
           "[\"namespace\"]\n"
           "\"integer\"=-0123456789\n"
           "\"string\"=\"value\"";

    os->close();

    os.reset();
}

const inline void InitParser()
{
    if (!parser->open("ini.ini")){
        std::cout << "bla" << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    CreateINIFile();
    InitParser();

    return EXIT_SUCCESS;
}
