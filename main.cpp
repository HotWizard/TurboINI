#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
    TurboINI::parser parser;

    if (!parser.open("test.ini"))
        return EXIT_FAILURE;

    if (parser.exists("string"))
        cout << "true" << endl;

    return EXIT_SUCCESS;
}
