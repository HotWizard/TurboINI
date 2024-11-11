#pragma once

#ifndef TURBOINI_TOOLS_HPP
#define TURBOINI_TOOLS_HPP

#include <string>

namespace TurboINI
{
    namespace tools
    {
        namespace string
        {
            const std::string TrimWhitespaces(const std::string &str);
            const decltype(std::string().size()) CountCharacters(const char &_char, const std::string &str);
        } // namespace string
    } // namespace tools
} // namespace TurboINI

#endif // TURBOINI_TOOLS_HPP
