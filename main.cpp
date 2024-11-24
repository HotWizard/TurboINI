#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>
#include <thread>

TurboINI::data INIFileData;
TurboINI::parser parser;

using TIDTI = TurboINI::DataTypes::integer;
using TIDTS = TurboINI::DataTypes::string;
using TIDTN = TurboINI::DataTypes::_namespace;

using TT = TurboINI::types;

const inline void InitInteger()
{
    INIFileData.GetIntegersVector().push_back(TIDTI("integer", 0));
}

const inline void InitString()
{
    INIFileData.GetStringsVector().push_back(TIDTS("string", "value"));
}

const inline void InitNamespace()
{
    INIFileData.GetNamespacesVector().push_back(TIDTN("namespace", {}, {}));
}

const inline void InitIntegerInNamespace()
{
    INIFileData.GetNamespacesVector().back().GetIntegers().push_back(TIDTI("integer", 0));
}

const inline void InitStringInNamespace()
{
    INIFileData.GetNamespacesVector().back().GetStrings().push_back(TIDTS("string", "value"));
}

const inline void InitINIFileData()
{
    InitInteger();
    InitString();
    InitNamespace();
    InitIntegerInNamespace();
    InitStringInNamespace();
}

const inline void InitParser()
{
    parser.SetData(INIFileData);
}

const inline void PrintInteger()
{
    if (parser.exists(TT::INTEGER, "integer"))
        std::cout << parser.GetInteger("integer") << std::endl;
}

const inline void PrintString()
{
    if (parser.exists(TT::STRING, "string"))
        std::cout << parser.get("string") << std::endl;
}

const inline void PrintIntegerFromNamespace()
{
    if (parser.ExistsInNamespace(TT::INTEGER, "namespace", "integer"))
        std::cout << parser.GetIntegerFromNamespace("namespace", "integer") << std::endl;
}

const inline void PrintStringFromNamespace()
{
    if (parser.ExistsInNamespace(TT::STRING, "namespace", "string"))
        std::cout << parser.GetFromNamespace("namespace", "string") << std::endl;
}

const inline void PrintNamespace()
{
    if (parser.NamespaceExists("namespace"))
    {
        PrintIntegerFromNamespace();
        PrintStringFromNamespace();
    }
}

const inline void print()
{
    PrintInteger();
    PrintString();
    PrintNamespace();
}

int main(void)
{
    InitINIFileData();
    InitParser();

    print();

    auto a = std::make_unique<std::thread>([&](void) { INIFileData = static_cast<TurboINI::data>(TurboINI::data()); }),
         b = std::make_unique<std::thread>([&](void) { parser.close(); });

    a->join();
    b->join();

    return EXIT_SUCCESS;
}
