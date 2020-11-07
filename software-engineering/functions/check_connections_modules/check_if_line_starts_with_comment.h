#pragma once
#include <string>

bool check_if_line_starts_with_comment(std::string line)
{
	if (line.length() >= 1)
		if (line.rfind("//", 0) != std::string::npos || line.rfind("/*", 0) != std::string::npos)
			return true;
	return false;
}
