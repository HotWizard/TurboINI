#include "parser.hpp"
#include "tools.hpp"

#include <cctype>
#include <filesystem>
#include <fstream>
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

inline bool IsString(std::string raw)
{
    using namespace TurboINI::tools::string;

    raw = TrimWhitespaces(raw);

    if (CountCharacters('"', raw) != 4 || CountCharacters('=', raw) < 1)
        return false;

    decltype(raw.size()) indexes[2];
    short CurrentIndexID = 0;

    for (decltype(raw.size()) i = 0; i < raw.size(); i++)
    {
        if (raw[i] == '"')
        {
            indexes[CurrentIndexID] = i;
            CurrentIndexID++;
        }
        if (CurrentIndexID == 2)
            break;
    }

    if (raw[indexes[1] + 1] != '=')
        return false;

    if (raw[indexes[1] + 2] != '"')
        return false;

    if (raw.back() != '"')
        return false;

    return true;
}

inline const std::string GetStringName(const std::string &str)
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

inline const std::string GetStringValue(const std::string &str)
{
    std::string output;

    bool n, j;

    for (const char &i : str)
    {
        if (i == '"' && n && j)
            break;
        if (i == '"' && n && !j)
        {
            j = true;
            continue;
        }
        if (i == '=' && !n && !j)
        {
            n = true;
            continue;
        }
        if (j)
            output += i;
    }

    return output;
}

inline void ProcessRawData(const std::string &raw)
{
    std::string temp;

    for (const char &i : raw)
    {
        temp += i;

        if (IsString(temp))
            TurboINI::data::strings.push_back({GetStringName(temp), GetStringValue(temp)});
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

void TurboINI::parser::close() const
{
}
