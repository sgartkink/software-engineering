#ifndef CHECK_CONNECTIONS_H
#define CHECK_CONNECTIONS_H

#include <iostream>
#include <fstream>
#include <list>

bool check_if_line_is_empty(const std::string &line);

//! \todo handle situation when () are in other line than function name
void check_connections(const std::list<std::string> &list_files)
{
    for (auto it = list_files.begin(); it != list_files.end(); ++it)
    {
        std::ifstream file;
        file.open(*it);

        std::cout << std::endl << "Checking functions for file: " << *it << std::endl;

        if (file.fail())
        {
            file.close();
            std::cout << "couldn't open file: " << *it;
            continue;
        }

        std::string previous_line;
        std::string line;

        // if this value is 0 we are looking for functions declarations
        // and if greater than 0 we check what functions a given function calls
        int brackets_amount = 0;

        while (!file.eof())
        {
            std::string current_line;
            getline(file, current_line);

            if (check_if_line_is_empty(current_line))
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

            // check if line starts with a comment
            //! \todo take into account a block of comments
            if (line.length() >= 1)
                if (line.rfind("//", 0) != std::string::npos || line.rfind("/*", 0) != std::string::npos)
                    continue;

            // function's definition when { is in other line
            if (previous_line.find("(") != std::string::npos && line.find("{") != std::string::npos && brackets_amount == 0)
            {
                int i = previous_line.find("(") - 1;
                for (; i >= 0; --i)
                    if (previous_line.at(i) == ' ')
                        break;

                std::string function_name = previous_line.substr(i + 1, previous_line.find("(") - i - 1);
                std::cout << std::endl << "Function: " << function_name << std::endl;
            }

            // function's definition when { is in the same line
            else if (line.find("(") != std::string::npos && line.find("{") != std::string::npos && brackets_amount == 0)
            {
                if (line.find("{") > line.find("("))
                {
                    int i = line.find("(") - 1;

                    // handle situations like:
                    // void function
                    // (args) {
                    if (i == -1)
                    {
                        i = previous_line.length() - 1;
                        for (; i > 0; --i)
                            if (previous_line.at(i) == ' ')
                                break;
                        std::cout << std::endl << "Function: " << previous_line.substr(i+1, previous_line.length()) << std::endl;
                    }
                    else
                    {
                        for (; i >= 0; --i)
                            if (line.at(i) == ' ')
                                break;

                        std::string function_name = line.substr(i + 1, line.find("(") - i - 1);
                        std::cout << std::endl << "Function: " << function_name << std::endl;
                    }

                    //cut line
                    line = line.substr(line.find("(") + 1, line.length());
                }
            }

            // to jest sprawdzenie po to żeby szukał tylko pomiędzy { }, wykluczenie przy okazji namespace, struct i class
            //! \todo handle situation when { } is only a scope
            //! \todo handle situation when { } are in the same line
            //! \todo } is in the end of the line
            // line.find('"{"') oznacza żeby nie brać pod uwagę ifów, w których ten warunek jest sprawdzany,
            // bo to "sztucznie nabijało"
            if (line.find("{") != std::string::npos && line.rfind("namespace", 0) == std::string::npos &&
                    line.rfind("class", 0) == std::string::npos && line.rfind("struct", 0) == std::string::npos
                    && line.find('"{"') == std::string::npos)
                brackets_amount++;
            if (line.find("}") != std::string::npos && brackets_amount > 0 && line.find('"}"') == std::string::npos)
                brackets_amount--;

            // handle situations like:
            // function
            // (args);
            if (line.rfind("(", 0) != std::string::npos && brackets_amount > 0)
            {
                int i = previous_line.length() - 1;
                for (; i > 0; --i)
                    if (previous_line.at(i) == ' ' || previous_line.at(i) == '?' || previous_line.at(i) == '.'
                            || previous_line.at(i) == '>' || previous_line.at(i) == '=' || previous_line.at(i) == '('
                            || previous_line.at(i) == '"' || previous_line.at(i) == '\'' || previous_line.at(i) == ']'
                            || previous_line.at(i) == ';' || previous_line.at(i) == '+' || previous_line.at(i) == '-'
                            || previous_line.at(i) == '!' || previous_line.at(i) == '%' || previous_line.at(i) == '^'
                            || previous_line.at(i) == '&' || previous_line.at(i) == '*' || previous_line.at(i) == '|')
                        break;
                std::cout << previous_line.substr(i + 1, previous_line.length()) << std::endl;
            }

            // szukamy użytych funkcji
            if (line.find("(") != std::string::npos && brackets_amount > 0)
            {
                std::string substring = line;

                while (substring.find("(") != std::string::npos)
                {
                    int i = substring.find("(") - 1;

                    // to handle situations like ((
                    if (i < 0)
                        i = 1;

                    // cut spaces before function name and (
                    if (substring.at(i) == ' ')
                    {
                        for (; i > 0; --i)
                            if (substring.at(i) != ' ')
                                break;
                        line = substring;
                        substring = substring.substr(0, i+1);
                    }

                    bool increment_i = false;
                    for (; i > 0; --i)
                        if (substring.at(i) == ' ' || substring.at(i) == ':' || substring.at(i) == '.' || substring.at(i) == '>'
                                || substring.at(i) == '=' || substring.at(i) == '(' || substring.at(i) == '"'
                                || substring.at(i) == '\'' || substring.at(i) == ']' || substring.at(i) == ';'
                                || substring.at(i) == '+' || substring.at(i) == '-' || substring.at(i) == '!' || substring.at(i) == '%'
                                || substring.at(i) == '^' || substring.at(i) == '&' || substring.at(i) == '*'
                                || substring.at(i) == '|' || substring.at(i) == '?')
                        {
                            increment_i = true;
                            break;
                        }

                    // check if it is object, like std::string str("string"), function here is std::string nor str
                    if (substring.at(i) == ' ')
                    {
                        int k = i;
                        //cut spaces
                        for (; k > 0; --k)
                            if (substring.at(k) != ' ')
                                break;

                        bool is_class = true;
                        for (int c = 0; c <= k; c++)
                            if (!((substring.at(c) >= 'a' && substring.at(c) <= 'z') ||
                                (substring.at(c) >= 'A' && substring.at(c) <= 'Z') ||
                                (substring.at(c) >= '0' && substring.at(c) <= '9') ||
                                  substring.at(c) == ':' || substring.at(c) == '_'))
                            {
                                is_class = false;
                                break;
                            }
                        if (is_class)
                        {
                            // to handle situation like else if
                            if (substring.substr(0, k+1) != "else")
                            {
                                std::cout << substring.substr(0, k+1) << std::endl;

                                substring = line;
                                substring = substring.substr(substring.find("(") + 1, substring.length());
                                line = substring;

                                continue;
                            }
                        }
                    }

                    // check if ( is between " or '
                    //! \todo handle situation when there is any from the chars above
                    //! in string between " and (
                    //! and there are more than one ( in quote
                    if (substring.at(i) != '"' && substring.at(i) != '\'')
                    {
                        if (increment_i)
                            i++;
                        std::string function_name = substring.substr(i, substring.find("(") - i);

                        //!\todo handle situation when there are spaces between ] and (
                        if (substring.at(i) == '[')
                        {
                            //lambda
                        }

                        if (function_name != "if" && function_name != "while" && function_name != "for"
                                && function_name.find(".") == std::string::npos && function_name.find("-") == std::string::npos
                                && function_name.find_first_not_of(' ') != std::string::npos
                                && function_name.find("!") == std::string::npos)
                        {
                            std::cout << function_name << std::endl;
                        }
                    }

                    substring = line;
                    substring = substring.substr(substring.find("(") + 1, substring.length());
                    line = substring;
                }
            }
        }
    }
}


bool check_if_line_is_empty(const std::string &line)
{
    for (unsigned int i = 0; i < line.length(); ++i)
        if (line.at(i) != ' ')
            return false;
    return true;
}

#endif // CHECK_CONNECTIONS_H
