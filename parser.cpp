#include "parser.hpp"

#include <cctype>
#include <filesystem>
#include <fstream>

namespace TurboINI
{
}

inline void process_raw_data(const std::string &raw) {
    
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
}

bool TurboINI::parser::open(const std::string &path) const
{
    if (!std::filesystem::exists(path))
        return false;

    return true;
}

void TurboINI::parser::close() const
{
}
