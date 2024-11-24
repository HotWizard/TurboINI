#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>

inline std::unique_ptr<TurboINI::parser> parser;

const inline void InitParser(const std::string &raw)
{
    parser = std::make_unique<TurboINI::parser>(raw);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        InitParser(argv[1]);

        if (parser->exists(TurboINI::types::INTEGER, "integer"))
            std::cout << parser->GetInteger("integer") << std::endl;
    }

    return EXIT_SUCCESS;
}
