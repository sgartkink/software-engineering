#pragma once

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "check_connections.h"

namespace check_namespaces{
    std::string strip_of_spaces(std::string file_name)
    {
        file_name.erase(std::remove(std::begin(file_name), std::end(file_name), ' '), std::end(file_name));
        file_name.erase(std::remove(std::begin(file_name), std::end(file_name), '"'), std::end(file_name));

        return file_name;
    };
	
    bool check_if_comment(std::string line)
    {
        if (line.find("//", 0) != std::string::npos || line.find("/*", 0) != std::string::npos)
            return true;
        else return false;
    }
	
	void check_connections(const std::list<std::string>& list_files)
	{
		for (auto it = list_files.begin(); it != list_files.end(); ++it)
		{
			std::ifstream file;
			file.open(*it);

			std::cout << std::endl << "Checking namespaces for file: " << *it << std::endl;

			if (file.fail())
			{
				file.close();
				std::cout << "couldn't open file: " << *it;
				continue;
			}

			std::string previous_line;
			std::string line;

			while (!file.eof())
			{
                std::string current_line;
                getline(file, current_line);

                if (check_functions::check_if_line_is_empty(current_line))
                    continue;

                // check if line starts with a comment
               //! \todo take into account a block of comments
                if (line.length() >= 1)
                    if (check_if_comment(line))
                        continue;

                if (previous_line.empty())
                {
                    previous_line = current_line;
                    line = current_line;
                }
                else
                {
                    previous_line = line;
                    line = current_line;
                }

                // remove spaces from the beginning of the line
                for (unsigned int i = 0; i < line.length(); i++)
                    if (line.at(i) != ' ')
                    {
                        line = line.substr(i, line.length());
                        break;
                    }              

                // namespace declaration when { in next line and is not a comment
                if (previous_line.find("namespace") != std::string::npos && line.find("{") != std::string::npos && !check_if_comment(previous_line))
                {
                    int i = previous_line.find("namespace") + 9;
                    for (; i <= previous_line.length(); ++i)
                        if (previous_line.at(i) == ' ')
                            break;

                    std::string namespace_name = previous_line.substr( i , previous_line.length() - i);
                    namespace_name = strip_of_spaces(namespace_name);
                    std::cout << std::endl << "Namespace: " << namespace_name << std::endl;
                }

                // namespace declaration when { in the same line and is not a comment
                else if (line.find("namespace") != std::string::npos && line.find("{") != std::string::npos && !check_if_comment(line))
                {
                    int i = line.find("namespace") + 9;
                    for (; i <= line.length(); ++i)
                        if (line.at(i) == ' ' || line.at(i) == '{')
                            break;

                    std::string namespace_name = line.substr(i, line.length() - i - 1);
                    namespace_name = strip_of_spaces(namespace_name);
                    std::cout << std::endl << "Namespace: " << namespace_name << std::endl;
                }
			}
		}
	}
}