#ifndef CHECK_CONNECTIONS_H
#define CHECK_CONNECTIONS_H

#include <iostream>
#include <fstream>
#include <list>

void check_connections(std::list<std::string> list_files) {
    for (auto it = list_files.begin(); it != list_files.end(); ++it)
    {
        std::ifstream file;
        file.open(*it);

        std::cout << std::endl << *it << std::endl << std::endl;

        if (file.fail())
        {
            file.close();
            std::cout << "couldn't open file: " << *it;
            continue;
        }

        std::string previous_line;
        std::string line;
        bool was_bracket = false;

        while (!file.eof())
        {
            if (previous_line.empty())
                getline(file, previous_line);
            else
            {
                if (line.empty())
                    getline(file, line);
                else
                {
                    previous_line = line;
                    getline(file, line);
                }
            }

            //definicja funkcji gdy { w nowej linii
            if (previous_line.find("(") != std::string::npos && line.find("{") != std::string::npos)
            {
                int i = previous_line.find("(") - 1;
                for (; i >= 0; --i)
                {
                    if (previous_line.at(i) == ' ')
                        break;
                }
                std::string function_name = previous_line.substr(i, previous_line.find("(") - i);
                if (function_name.find("if") == std::string::npos && function_name.find("while") == std::string::npos &&
                        function_name.find("for") == std::string::npos && function_name.find(".") == std::string::npos &&
                        function_name.find("-") == std::string::npos && function_name.find_first_not_of(' ') != std::string::npos)
                {
//                    std::cout << function_name << std::endl;
                }
            }

            //definicja funkcji gdy { w tej samej linii
            else if (line.find("(") != std::string::npos && line.find("{") != std::string::npos)
            {
                if (line.find("{") > line.find("("))
                {
                    int i = line.find("(") - 1;
                    for (; i >= 0; --i)
                    {
                        if (line.at(i) == ' ')
                            break;
                    }
                    std::string function_name = line.substr(i, line.find("(") - i);
                    if (function_name.find("if") == std::string::npos && function_name.find("while") == std::string::npos &&
                            function_name.find("for") == std::string::npos && function_name.find(".") == std::string::npos &&
                            function_name.find("-") == std::string::npos && function_name.find_first_not_of(' ') != std::string::npos)
                    {
//                        std::cout << function_name << std::endl;
                    }
                }
            }

            //szukamy użytych funkcji
            else if (line.find("(") != std::string::npos && was_bracket)
            {
                std::string substring = line;

                while (substring.find("(") != std::string::npos)
                {
                    int i = substring.find("(") - 1;
                    for (; i >= 0; --i)
                    {
                        if (substring.at(i) == ' ' || substring.at(i) == ':' || substring.at(i) == '.' || substring.at(i) == '>'
                                || substring.at(i) == '=' || substring.at(i) == '(')
                            break;
                    }

                    std::string function_name = substring.substr(i + 1, substring.find("(") - i - 1);
                    if (function_name.find("if") == std::string::npos && function_name.find("while") == std::string::npos &&
                            function_name.find("for") == std::string::npos && function_name.find(".") == std::string::npos &&
                            function_name.find("-") == std::string::npos && function_name.find_first_not_of(' ') != std::string::npos)
                    {
                        std::cout << function_name << std::endl;
                    }
                    substring = substring.substr(substring.find("(") + 1, substring.length() - substring.find("("));
                }
            }

            //to jest sprawdzenie po to żeby szukał tylko pomiędzy { }
            if (line.find("{") != std::string::npos)
                was_bracket = true;
            else if (line.find("}") != std::string::npos)
                was_bracket = false;
        }
    }
}

#endif // CHECK_CONNECTIONS_H
