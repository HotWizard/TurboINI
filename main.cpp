#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>

using TIT = TurboINI::types;

inline std::unique_ptr<TurboINI::parser> parser;

const inline void InitParser(const std::string &raw)
{
    parser = std::make_unique<TurboINI::parser>(raw);
}

int main(void)
{
    InitParser("\"integer\"=324");

    if (parser->exists(TIT::INTEGER, "integer"))
        std::cout << parser->GetInteger("integer") << std::endl;

    return EXIT_SUCCESS;
}
