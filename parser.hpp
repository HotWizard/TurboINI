#pragma once

#ifndef TURBOINI_PARSER_HPP
#define TURBOINI_PARSER_HPP

#include <string>

namespace TurboINI
{
    class parser
    {
      public:
        parser() = default;
        parser(const std::string &path);

        bool open(const std::string &path) const;

        void close() const;
    };
} // namespace TurboINI

#endif // TURBOINI_PARSER_HPP
