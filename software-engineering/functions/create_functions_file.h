#pragma once

#include <vector>
#include "../structs/FunctionConnections.h"

void create_functions_file(std::vector<FunctionConnections> connections)
{
    std::vector<std::string> shown_filenames;
    std::ofstream functionFile;
    functionFile.open("functions.txt", std::ofstream::out | std::ofstream::trunc);

    for (auto connection : connections)
    {
        std::size_t found = connection.get_file_name().find_last_of("\\");
        std::string function_name = connection.get_function_name();
        std::string file_name = connection.get_file_name().substr(found + 1, connection.get_file_name().length());

        std::vector<std::string>::iterator it;
        it = std::find(shown_filenames.begin(), shown_filenames.end(), file_name);

        if (it == shown_filenames.end())
        {
            functionFile << "\nFile name: " << file_name << "\n\n";
            shown_filenames.push_back(file_name);
        }

        functionFile << function_name << "\n";

    }

    functionFile.close();
}
