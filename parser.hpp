#pragma once

#ifndef TURBOINI_PARSER_HPP
#define TURBOINI_PARSER_HPP

#include "data.hpp"

#include <string>

namespace TurboINI
{
    enum types
    {
        INTEGER,
        STRING,
        NAMESPACE
    };
    class parser
    {
      public:
        explicit parser();
        explicit parser(const std::string &raw);
        ~parser();

        const bool open(const std::string &path) const, exists(const types &type, const std::string &key) const,
            NamespaceExists(const std::string &key) const,
            ExistsInNamespace(const types &type, const std::string &NamespaceKey, const std::string &key) const;

        const long long &GetInteger(const std::string &key);

        const std::string &get(const std::string &key) const,
            &GetFromNamespace(const std::string &NamespaceKey, const std::string &key) const;

        const long long &GetIntegerFromNamespace(const std::string &NamespaceKey, const std::string &key) const;

        void close(void) const, EnableRefreshing(const bool &status) const,
            SetRefreshRate(const double &milliseconds) const, SetData(const data &_data) const,
            ParseRaw(const std::string &raw) const;

        const data &GetData() const;
    };
} // namespace TurboINI

#endif // TURBOINI_PARSER_HPP
