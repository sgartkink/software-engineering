#pragma once
#include <string>

bool check_if_line_is_empty(const std::string& line)
{
    for (unsigned int i = 0; i < line.length(); ++i)
        if (line.at(i) != ' ')
            return false;
    return true;
}
