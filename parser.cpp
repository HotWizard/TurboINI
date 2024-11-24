#include "parser.hpp"
#include "data.hpp"
#include "tools.hpp"

#include <cctype>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <memory>
#include <thread>
#include <vector>

namespace TurboINI
{
    data INIData;

    namespace ParserSettings
    {
        std::string path;
        bool refresh = false;
        double RefreshRate = 0.5;
        std::chrono::time_point<std::chrono::steady_clock> RefreshTimePoint;
    } // namespace ParserSettings
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

const inline bool IsInteger(std::string raw)
{
    raw = TurboINI::tools::string::TrimWhitespaces(raw);

    if (!IsDataType(raw))
        return false;

    if (TurboINI::tools::string::CountCharacters('"', raw) != 2)
        return false;

    std::string temp;

    for (decltype(raw.size()) i = raw.size() - 1; i >= 0; i--)
    {
        if (raw[i] == '=')
            break;

        temp += raw[i];
    }

    if (temp.empty())
        return false;

    const char allowed[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for (decltype(temp.size()) i = 0; i < temp.size(); i++)
    {
        bool b;

        for (const char &c : allowed)
        {
            if (temp[i] == c)
                b = true;
        }

        if (!b)
            return false;
    }

    return true;
}

const inline std::string GetName(const std::string &str)
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

const inline long long GetIntegerValue(const std::string &raw)
{
    std::string output;

    for (decltype(raw.size()) i = raw.size() - 1; i >= 0; i--)
    {
        if (raw[i] == '=')
            break;

        output += raw[i];
    }

    return std::stoll(std::string(output.rbegin(), output.rend()));
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

    for (decltype(raw.size()) i = 0; i < raw.size(); i++)
    {
        temp += raw[i];

        if (!NamespaceDetected)
        {
            if (IsString(temp))
            {
                TurboINI::INIData.GetStringsVector().push_back(
                    TurboINI::DataTypes::string(GetName(temp), GetStringValue(temp)));

                temp.clear();
            }
            else if (IsInteger(temp))
            {
                if (i == raw.size() - 1 || std::isspace(temp.back()) ||
                    (i + 1 < raw.size() && (raw[i + 1] == '"' || raw[i + 1] == '[')))
                {
                    TurboINI::INIData.GetIntegersVector().push_back(
                        TurboINI::DataTypes::integer(GetName(temp), GetIntegerValue(temp)));

                    temp.clear();
                }
            }
        }
        else
        {
            if (IsString(temp))
            {
                TurboINI::INIData.GetNamespacesVector().back().GetStrings().push_back(
                    TurboINI::DataTypes::string(GetName(temp), GetStringValue(temp)));

                temp.clear();
            }
            else if (IsInteger(temp))
            {
                TurboINI::INIData.GetNamespacesVector().back().GetIntegers().push_back(
                    TurboINI::DataTypes::integer(GetName(temp), GetIntegerValue(temp)));

                temp.clear();
            }
        }

        if (IsNamespace(temp))
        {
            TurboINI::INIData.GetNamespacesVector().emplace_back();
            TurboINI::INIData.GetNamespacesVector().back().SetKey(GetNamespaceName(temp));

            NamespaceDetected = true;

            temp.clear();
        }
    }

    temp.clear();
}

inline void ClearData(void)
{
    TurboINI::INIData.clear();
}

inline void parse(const std::string &path)
{
    ClearData();

    std::unique_ptr<std::ifstream> is = std::make_unique<std::ifstream>(path);

    std::string temp_line, raw;

    while (std::getline(*is, temp_line))
    {
        if (std::isspace(temp_line.back()))
            temp_line.pop_back();

        raw += temp_line;
    }

    auto a = std::make_unique<std::thread>([&](void) { temp_line.clear(); }),
         b = std::make_unique<std::thread>([&](void) { (*is).close(); });

    a->join();
    b->join();

    ProcessRawData(raw);
}

inline void refresh(void)
{
    if (TurboINI::ParserSettings::refresh)
    {
        if (std::chrono::duration<double>(std::chrono::steady_clock::now() - TurboINI::ParserSettings::RefreshTimePoint)
                .count() >= TurboINI::ParserSettings::RefreshRate)
        {
            TurboINI::ParserSettings::RefreshTimePoint = std::chrono::steady_clock::now();

            parse(TurboINI::ParserSettings::path);
        }
    }
}

TurboINI::parser::parser()
{
    ParserSettings::RefreshTimePoint = std::chrono::steady_clock::now();
}

TurboINI::parser::parser(const std::string &raw)
{
    ParseRaw(raw);
}

TurboINI::parser::~parser()
{
    close();
}

const bool TurboINI::parser::open(const std::string &path) const
{
    if (!std::filesystem::exists(path))
        return false;

    TurboINI::ParserSettings::path = path;

    parse(path);

    return true;
}

const bool TurboINI::parser::exists(const types &type, const std::string &key) const
{
    refresh();

    if (type == types::INTEGER)
    {
        for (const auto &i : TurboINI::INIData.GetIntegersVector())
        {
            if (i.GetKey() == key)
                return true;
        }
    }
    else if (type == types::STRING)
    {
        for (const auto &i : TurboINI::INIData.GetStringsVector())
        {
            if (i.GetKey() == key)
                return true;
        }
    }

    return false;
}

const bool TurboINI::parser::NamespaceExists(const std::string &key) const
{
    refresh();

    for (const auto &i : TurboINI::INIData.GetNamespacesVector())
    {
        if (i.GetKey() == key)
            return true;
    }

    return false;
}

const bool TurboINI::parser::ExistsInNamespace(const types &type, const std::string &NamespaceKey,
                                               const std::string &key) const
{
    refresh();

    for (const auto &i : TurboINI::INIData.GetNamespacesVector())
    {
        if (i.GetKey() == NamespaceKey)
        {
            if (type == types::INTEGER)
            {
                for (const auto &j : i.GetIntegers())
                {
                    if (j.GetKey() == key)
                        return true;
                }
            }
            else if (type == types::STRING)
            {
                for (const auto &j : i.GetStrings())
                {
                    if (j.GetKey() == key)
                        return true;
                }
            }
        }
    }

    return false;
}

const long long &TurboINI::parser::GetInteger(const std::string &key)
{
    refresh();

    std::unique_ptr<const long long *> output;

    for (auto &i : INIData.GetIntegersVector())
    {
        if (i.GetKey() == key)
            output = std::make_unique<const long long *>(&i.GetValue());
    }

    return **output;
}

const std::string &TurboINI::parser::get(const std::string &key) const
{
    refresh();

    std::unique_ptr<const std::string *> output;

    for (auto &i : INIData.GetStringsVector())
    {
        if (i.GetKey() == key)
            output = std::make_unique<const std::string *>(&i.GetValue());
    }

    return **output;
}

const std::string &TurboINI::parser::GetFromNamespace(const std::string &NamespaceKey, const std::string &key) const
{
    refresh();

    std::unique_ptr<const std::string *> output;

    for (auto &i : INIData.GetNamespacesVector())
    {
        if (i.GetKey() == NamespaceKey)
        {
            for (auto &j : i.GetStrings())
            {
                if (j.GetKey() == key)
                    output = std::make_unique<const std::string *>(&j.GetValue());
            }
        }
    }

    return **output;
}

void TurboINI::parser::close(void) const
{
    ClearData();
}

const long long &TurboINI::parser::GetIntegerFromNamespace(const std::string &NamespaceKey,
                                                           const std::string &key) const
{
    std::unique_ptr<const long long *> output;

    for (auto &i : INIData.GetNamespacesVector())
    {
        if (i.GetKey() == NamespaceKey)
        {
            for (auto &j : i.GetIntegers())
            {
                if (j.GetKey() == key)
                    output = std::make_unique<const long long *>(&j.GetValue());
            }
        }
    }

    return **output;
}

void TurboINI::parser::EnableRefreshing(const bool &status) const
{
    TurboINI::ParserSettings::refresh = status;
}

void TurboINI::parser::SetRefreshRate(const double &milliseconds) const
{
    TurboINI::ParserSettings::RefreshRate = milliseconds;
}

void TurboINI::parser::SetData(const data &_data) const
{
    INIData = _data;
}

void TurboINI::parser::ParseRaw(const std::string &raw) const
{
    ProcessRawData(raw);
}

const TurboINI::data &TurboINI::parser::GetData() const
{
    return INIData;
}
