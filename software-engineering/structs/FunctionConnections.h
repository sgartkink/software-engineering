#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <map>

struct FunctionConnections
{
    std::string _file_name;
    std::string _function_name;
    std::string _namespace = "empty";
    std::map<std::string, int> _number_of_function_calls;

    FunctionConnections(std::string function_name, std::string file_name)
    {
        _function_name = function_name;
        _file_name = file_name;
    }

    void add_new_function(const std::string& func)
    {
        _number_of_function_calls[func]++;
    }

    void show_connections()
    {
        std::cout << std::endl << "Function: " << _function_name << std::endl;
        for (auto it = _number_of_function_calls.begin(); it != _number_of_function_calls.end(); ++it)
            std::cout << "calls: " << it->first << " " << it->second << " time\\times" << std::endl;
        std::cout << std::endl;
    }
	
    void connections_to_graph(std::string name, std::vector<std::string> functions_list)
    {
        std::fstream x;
        x.open(name, std::ios::out | std::ios::app);
        for (auto it = _number_of_function_calls.begin(); it != _number_of_function_calls.end(); ++it)
            x << '"' << _function_name << '"' << "->" << '"' << it->first << '"' << "[label = " << it->second << " ];\n";
        x.close();
    }

	std::string get_function_name()
    {
        return _function_name;
    }

    std::string get_file_name()
    {
        return _file_name;
    }
};

