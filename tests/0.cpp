#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
    TurboINI::parser parser;

    parser.open(argv[1]);
    parser.EnableRefreshing(true);
    parser.SetRefreshRate(0.5);

    for (long long i = 0; i < 1000000; i++)
    {
        if (parser.exists(TurboINI::types::INTEGER, "integer"))
            parser.GetInteger("integer");
    }

    parser.close();

    return EXIT_SUCCESS;
}
