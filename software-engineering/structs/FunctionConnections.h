#pragma once
#include <iostream>
#include <ostream>

struct FunctionConnections
{
    std::string _function_name;
    std::string _namespace = "empty";
    std::map<std::string, int> _number_of_function_calls;

    FunctionConnections(std::string function_name)
    {
        _function_name = function_name;
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
};

