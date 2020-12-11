#pragma once
#include <string>

bool check_if_line_starts_with_comment(std::string line, bool &multiline)
{
    if (multiline)
    {
        if (line.find("*/") == std::string::npos)
            return true;
        else if (line.find("*/") != std::string::npos && line.find("*/") == line.size() - 2)
        {
            multiline = false;
            return true;
        }
        else
        {
            line = line.substr(line.size() - line.find("*/") - 2, line.size()-1);
            multiline = false;
            return false;
        }
    }
    else
    {
        if (line.size() < 2)
            return false;

        if (line.find("//") == 0)
            return true;
        else if (line.find("/*") == 0)
        {
            multiline = true;
            return true;
        }

       return false;
    }

}
