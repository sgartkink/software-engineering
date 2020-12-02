#include <iostream>
#include <fstream>
#include <list>
#include <vector>


#include "../structs/FunctionConnections.h"
#include "check_connections_modules/check_if_line_is_empty.h"
#include "check_connections_modules/check_if_line_starts_with_comment.h"
#include "check_connections_modules/increment_bracket_count.h"
#include "check_connections_modules/should_increment.h"

struct NamespaceConnections {  //! \todo extract this struct into separate file
    std::string _file_name;
    std::string _namespace_name;
    std::vector<std::string> _functions_included;
    std::vector<std::string> _namespaces_included; //! \todo

    void show_included_function()
    {
        std::cout << "Namespace: " << _namespace_name << " includes: " << std::endl;
        for (const std::string& func : _functions_included)
            std::cout << func << std::endl;
        std::cout << std::endl;
    }

    void functions_namespaces_to_graph(std::string file_name) {
        std::ofstream file;
        static int cluster = 0;
        file.open(file_name, std::ofstream::out | std::ofstream::app);
        file << "\nsubgraph cluster" << cluster << "\n{\nnode[style = filled,color = white];\nstyle = filled;\ncolor = lightgrey;\n" << '"' << _namespace_name << '"' << " [shape = hexagon];\n";
        for (const std::string& func : _functions_included) {
            file << '"' << _namespace_name << '"' << "->" << '"' << func << '"' << "\n";
            ++cluster;
        }
        file << "}\n";
        file.close();
    }

    void functions_namespaces_to_graph2(std::string file_name) {
        std::ofstream file;
        file.open(file_name, std::ofstream::out | std::ofstream::app);
        for (const std::string& func : _functions_included) {
            file << '"' << _namespace_name << '"' << "->" << '"' << func << '"' << "\n";
        }
        file.close();
    }

    std::string get_file_name()
    {
        return _file_name;
    }

    std::string get_namespace_name()
    {
        return _namespace_name;
    }

    std::vector<std::string> get_included_functions()
    {
        return _functions_included;
    }
};

//! \todo handle situation when () are in other line than function name
void check_connections(const std::list<std::string>& list_files,
    std::vector<FunctionConnections>& connections,
    std::vector<NamespaceConnections>& namespaces)
{
    FunctionConnections* current_connection = nullptr;
    NamespaceConnections* current_namespace = nullptr;

    for (auto it = list_files.begin(); it != list_files.end(); ++it)
    {
        std::ifstream file;
        file.open(*it);

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

        bool is_namespace = false;

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
            if (check_if_line_starts_with_comment(line))
                continue;

            // function's definition when { is in other line
            if (previous_line.find("(") != std::string::npos && line.find("{") != std::string::npos && brackets_amount == 0)
            {
                int i = previous_line.find("(") - 1;
                for (; i >= 0; --i)
                    if (previous_line.at(i) == ' ')
                        break;

                std::string function_name = previous_line.substr(i + 1, previous_line.find("(") - i - 1);
                FunctionConnections func(function_name, *it);
                connections.push_back(func);
                current_connection = &connections[connections.size() - 1];

                if (current_namespace != nullptr)
                {
                    current_namespace->_functions_included.push_back(function_name);
                    current_connection->_namespace = current_namespace->_namespace_name;
                }
            }

            //namespace's name when { is in other line
            else if (previous_line.rfind("namespace", 0) != std::string::npos && line.find("{") != std::string::npos && !is_namespace && brackets_amount == 0
                && previous_line.find("{") == std::string::npos)
            {
                std::string namespace_name = previous_line.substr(10);
                unsigned int i = 0;
                for (; i < namespace_name.size(); ++i)
                    if (namespace_name.at(i) != ' ')
                        break;

                namespace_name.substr(i);
                i = namespace_name.size() - 1;

                for (; i > 0; --i)
                    if (namespace_name.at(i) != ' ')
                        break;

                namespace_name.substr(0, i);

                NamespaceConnections namespace_connection;
                namespace_connection._namespace_name = namespace_name;
                namespace_connection._file_name = *it;
                namespaces.push_back(namespace_connection);
                current_namespace = &namespaces[namespaces.size() - 1];
                is_namespace = true;
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

                        std::string function_name = previous_line.substr(i + 1, previous_line.length());
                        FunctionConnections func(function_name, *it);
                        connections.push_back(func);
                        current_connection = &connections[connections.size() - 1];

                        if (current_namespace != nullptr)
                        {
                            current_namespace->_functions_included.push_back(function_name);
                            current_connection->_namespace = current_namespace->_namespace_name;
                        }
                    }
                    else
                    {
                        for (; i >= 0; --i)
                            if (line.at(i) == ' ')
                                break;

                        std::string function_name = line.substr(i + 1, line.find("(") - i - 1);
                        FunctionConnections func(function_name, *it);
                        connections.push_back(func);
                        current_connection = &connections[connections.size() - 1];

                        if (current_namespace != nullptr)
                        {
                            current_namespace->_functions_included.push_back(function_name);
                            current_connection->_namespace = current_namespace->_namespace_name;
                        }
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
            if (increment_bracket_count(line))
                brackets_amount++;

            else if (line.find("{") != std::string::npos && line.rfind("namespace", 0) != std::string::npos && !is_namespace)
            {
                unsigned int i = 10;
                for (; i < line.size(); ++i)
                    if (line.at(i) != ' ')
                        break;

                unsigned int k = i;
                for (; k < line.size(); ++k)
                    if (line.at(k) == ' ' || line.at(k) == '{')
                        break;

                std::string namespace_name = line.substr(i, k - i);
                NamespaceConnections namespace_connection;
                namespace_connection._namespace_name = namespace_name;
                namespace_connection._file_name = *it;
                namespaces.push_back(namespace_connection);
                current_namespace = &namespaces[namespaces.size() - 1];

                is_namespace = true;
            }

            if (line.find("}") != std::string::npos && brackets_amount > 0 && line.find('"}"') == std::string::npos)
                brackets_amount--;
            else if (line.find("}") != std::string::npos && brackets_amount == 0 && line.find('"}"') == std::string::npos
                && is_namespace == true)
            {
                current_namespace = nullptr;
                is_namespace = false;
            }

            // handle situations like:
            // function
            // (args);
            if (line.rfind("(", 0) != std::string::npos && brackets_amount > 0)
            {
                int i = previous_line.length() - 1;
                for (; i > 0; --i)
                    if (should_increment(previous_line, i))
                        break;
                //                std::cout << previous_line.substr(i + 1, previous_line.length()) << std::endl;
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
                        substring = substring.substr(0, i + 1);
                    }

                    bool increment_i = false;
                    for (; i > 0; --i)
                        if (should_increment(substring, i))
                        {
                            increment_i = true;
                            break;
                        }

                    // check if it is object, like std::string str("string"), function here is std::string not str
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
                            if (substring.substr(0, k + 1) != "else")
                            {
                                std::string function_name = substring.substr(0, k + 1);
                                current_connection->add_new_function(function_name);

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
                        if (substring.at(i) == ']')
                        {
                            current_connection->add_new_function("lambda");
                        }

                        if (function_name != "if" && function_name != "while" && function_name != "for" && function_name != "switch"
                            && function_name.find(".") == std::string::npos && function_name.find("-") == std::string::npos
                            && function_name.find_first_not_of(' ') != std::string::npos
                            && function_name.find("!") == std::string::npos)
                        {
                            current_connection->add_new_function(function_name);
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