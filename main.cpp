#include "TurboINI.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

int main(void)
{
    TurboINI::parser parser;

    parser.open("test.ini");
    parser.EnableRefreshing(true);

    if (parser.exists(TurboINI::types::INTEGER, "integer"))
        cout << parser.GetInteger("integer") << endl;

    for (int i = 0; i < 1000000; i++)
        parser.GetInteger("integer");

    parser.close();

    return EXIT_SUCCESS;
}
