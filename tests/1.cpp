#include "../TurboINI.hpp"

#include <iostream>
#include <memory>

inline std::unique_ptr<TurboINI::parser> parser;

const inline void InitParser()
{
    parser = std::make_unique<TurboINI::parser>("\"integer\"=-0123456789");
}

int main(void)
{
    InitParser();

    if (parser->exists(TurboINI::types::INTEGER, "integer"))
        std::cout << parser->GetInteger("integer") << std::endl;
    if (parser->exists(TurboINI::types::STRING, "string"))
        std::cout << parser->get("string") << std::endl;
    if (parser->NamespaceExists("namespace"))
    {
        if (parser->ExistsInNamespace(TurboINI::types::INTEGER, "namespace", "integer"))
            std::cout << parser->GetIntegerFromNamespace("namespace", "integer") << std::endl;
        if (parser->ExistsInNamespace(TurboINI::types::STRING, "namespace", "string"))
            std::cout << parser->GetFromNamespace("namespace", "string") << std::endl;
    }

    return EXIT_SUCCESS;
}
