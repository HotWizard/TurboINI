#include "TurboINI.hpp"

#include <iostream>

int main(void)
{
    TurboINI::parser parser;
    TurboINI::data data({TurboINI::DataTypes::integer("integer", 1)}, {TurboINI::DataTypes::string("string", "value")},
                        {TurboINI::DataTypes::_namespace("namespace", {TurboINI::DataTypes::integer("integer", 1)},
                                                         {TurboINI::DataTypes::string("string", "value")})});
    parser.SetData(data);

    if (parser.exists(TurboINI::types::INTEGER, "integer"))
        std::cout << parser.GetInteger("integer") << std::endl;

    if (parser.exists(TurboINI::types::STRING, "string"))
        std::cout << parser.get("string") << std::endl;

    if (parser.NamespaceExists("namespace"))
    {
        if (parser.ExistsInNamespace(TurboINI::types::INTEGER, "namespace", "integer"))
            std::cout << parser.GetIntegerFromNamespace("namespace", "integer") << std::endl;
        if (parser.ExistsInNamespace(TurboINI::types::STRING, "namespace", "string"))
            std::cout << parser.GetFromNamespace("namespace", "string") << std::endl;
    }

    return EXIT_SUCCESS;
}
