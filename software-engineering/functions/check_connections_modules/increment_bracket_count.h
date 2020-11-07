#pragma once
#include <string>

bool increment_bracket_count(std::string line)
{
    if (line.find("{") != std::string::npos && line.rfind("namespace", 0) == std::string::npos &&
        line.rfind("class", 0) == std::string::npos && line.rfind("struct", 0) == std::string::npos
        && line.find('"{"') == std::string::npos && line.find("'{'") == std::string::npos)
        return true;
    return false;
}
