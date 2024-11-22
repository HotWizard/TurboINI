#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>
#include <memory>

using namespace std;

unique_ptr<TurboINI::parser> parser;

const inline void init(const std::string &path)
{
    parser = make_unique<TurboINI::parser>();

    parser->EnableRefreshing(true);

    if (!parser->open(path))
        exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        init(argv[1]);

        if (parser->exists(TurboINI::types::INTEGER, "integer"))
            cout << parser->GetInteger("integer") << endl;
        if (parser->exists(TurboINI::types::STRING, "string"))
            cout << parser->get("string") << endl;
        if (parser->NamespaceExists("namespace"))
        {
            if (parser->ExistsInNamespace(TurboINI::types::INTEGER, "namespace", "integer"))
                cout << parser->GetIntegerFromNamespace("namespace", "integer") << endl;
            if (parser->ExistsInNamespace(TurboINI::types::STRING, "namespace", "string"))
                cout << parser->GetFromNamespace("namespace", "string") << endl;
        }
    }

    return EXIT_SUCCESS;
}
