#include "parser.hpp"
#include "tools.hpp"

#include <cctype>
#include <filesystem>
#include <fstream>
#include <memory>
#include <vector>

namespace TurboINI
{
    namespace data
    {
        struct _string
        {
            std::string key, value;
        };

        struct _namespace
        {
            std::string key;
            std::vector<_string> strings;
        };

        std::vector<_string> strings;
        std::vector<_namespace> namespaces;
    } // namespace data
} // namespace TurboINI

const inline bool IsDataType(std::string raw)
{
    raw = TurboINI::tools::string::TrimWhitespaces(raw);

    if (TurboINI::tools::string::CountCharacters('"', raw) < 2 ||
        TurboINI::tools::string::CountCharacters('=', raw) == 0 || raw[0] != '"')
        return false;

    for (decltype(raw.size()) i = 1; i < raw.size(); i++)
    {
        if (raw[i] == '"')
        {
            if (i + 1 == raw.size() || raw[i + 1] != '=')
                return false;
            break;
        }
    }

    return true;
}

const inline bool IsString(std::string raw)
{
    if (!IsDataType(raw) || TurboINI::tools::string::CountCharacters('"', raw) != 4)
        return false;

    raw = TurboINI::tools::string::TrimWhitespaces(raw);

    if (raw.back() != '"')
        return false;

    for (decltype(raw.size()) i = 1; i < raw.size(); i++)
    {
        if (raw[i] == '=')
        {
            if (i + 1 > raw.size() || raw[i + 1] != '"')
                return false;
            break;
        }
    }

    return true;
}

const inline bool IsNamespace(std::string raw)
{
    raw = TurboINI::tools::string::TrimWhitespaces(raw);

    if (raw.size() > 4)
    {
        if (raw[0] != '[' || raw[1] != '"' || raw[raw.size() - 2] != '"' || raw.back() != ']')
            return false;
    }
    else if (raw.size() < 5)
        return false;

    return true;
}

const inline std::string GetStringName(const std::string &str)
{
    std::string output;

    bool n;

    for (const char &i : str)
    {
        if (i == '"' && !n)
        {
            n = true;
            continue;
        }
        else if (i == '"' && n)
            break;
        if (n)
            output += i;
    }

    return output;
}

const inline std::string GetStringValue(const std::string &str)
{
    std::string output;

    bool a, b, n;

    for (const char &c : str)
    {
        if (!n)
        {
            if (c == '"')
            {
                if (!a)
                    a = true;
                else
                    b = true;
            }
            if (b && c == '=')
            {
                n = true;
                a = false;
                b = false;
            }
        }
        else
        {
            if (a && c == '"')
                break;
            if (c == '"')
            {
                a = true;
                continue;
            }
            if (a)
                output += c;
        }
    }

    return output;
}

const inline std::string GetNamespaceName(const std::string &raw)
{
    std::string output;

    bool a;

    for (const char &i : raw)
    {
        if (i == '"' && a)
            break;
        if (a)
            output += i;
        if (i == '"' && !a)
        {
            a = true;
            continue;
        }
    }

    return output;
}

inline void ProcessRawData(const std::string &raw)
{
    std::string temp;

    bool NamespaceDetected;

    for (const char &i : raw)
    {
        temp += i;

        if (!NamespaceDetected)
        {
            if (IsString(temp))
            {
                TurboINI::data::strings.push_back({GetStringName(temp), GetStringValue(temp)});
                temp.clear();
            }
        }
        else
        {
            if (IsString(temp))
            {
                TurboINI::data::namespaces.back().strings.push_back({GetStringName(temp), GetStringValue(temp)});
                temp.clear();
            }
        }

        if (IsNamespace(temp))
        {
            TurboINI::data::namespaces.push_back({GetNamespaceName(temp)});

            NamespaceDetected = true;

            temp.clear();
        }
    }
}

inline void parse(const std::string &path)
{
    std::ifstream is(path);

    std::string temp_line, raw;

    while (std::getline(is, temp_line))
    {
        if (std::isspace(temp_line.back()))
            temp_line.pop_back();

        raw += temp_line;
    }

    ProcessRawData(raw);
}

const bool TurboINI::parser::open(const std::string &path) const
{
    if (!std::filesystem::exists(path))
        return false;

    parse(path);

    ProcessRawData(path);

    return true;
}

const bool TurboINI::parser::exists(const std::string &key) const
{
    for (const auto &i : TurboINI::data::strings)
    {
        if (i.key == key)
            return true;
    }

    return false;
}

const bool TurboINI::parser::NamespaceExists(const std::string &key) const
{
    for (const auto &i : TurboINI::data::namespaces)
    {
        if (i.key == key)
            return true;
    }

    return false;
}

const bool TurboINI::parser::ExistsInNamespace(const std::string &NamespaceKey, const std::string &key) const
{
    for (const auto &i : TurboINI::data::namespaces)
    {
        if (i.key == NamespaceKey)
        {
            for (const auto &j : i.strings)
            {
                if (j.key == key)
                    return true;
            }
        }
    }

    return false;
}

const std::string &TurboINI::parser::get(const std::string &key) const
{
    std::unique_ptr<std::string *> output;

    for (auto &i : TurboINI::data::strings)
    {
        if (i.key == key)
            output = std::make_unique<std::string *>(&i.value);
    }

    return **output;
}

const std::string &TurboINI::parser::GetFromNamespace(const std::string &NamespaceKey, const std::string &key) const
{
    std::unique_ptr<std::string *> output;

    for (auto &i : TurboINI::data::namespaces)
    {
        if (i.key == NamespaceKey)
        {
            for (auto &j : i.strings)
            {
                if (j.key == key)
                    output = std::make_unique<std::string *>(&j.value);
            }
        }
    }

    return **output;
}

void TurboINI::parser::close() const
{
    TurboINI::data::strings.clear();
    TurboINI::data::namespaces.clear();
}
