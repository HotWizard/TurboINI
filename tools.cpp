#include "tools.hpp"

#include <cctype>

const std::string TurboINI::tools::string::TrimWhitespaces(const std::string &str)
{
    std::string output;

    for (const char &i : str)
    {
        if (!std::isspace(i))
            output += i;
    }

    return output;
}

const decltype(std::string().size()) TurboINI::tools::string::CountCharacters(const char &_char,
                                                                                     const std::string &str)
{
    decltype(std::string().size()) output = 0;

    for (const char &i : str)
    {
        if (i == _char)
            output++;
    }

    return output;
}
