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

        const bool open(const std::string &path) const, exists(const std::string &key) const,
            NamespaceExists(const std::string &key) const,
            ExistsInNamespace(const std::string &NamespaceKey, const std::string &key) const;

        const std::string &get(const std::string &key) const,
            &GetFromNamespace(const std::string &NamespaceKey, const std::string &key) const;

        void close() const;
    };
} // namespace TurboINI

#endif // TURBOINI_PARSER_HPP
