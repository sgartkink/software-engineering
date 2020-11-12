#pragma once

#include "../structs/ProjectConnections.h"

void display_connections(ProjectConnections projectConnections)
{
    for (auto connection : projectConnections.getFunctionConnections())
        connection.show_connections();

    for (auto name : projectConnections.getNamespaceConnections())
        name.show_included_function();

    for (auto connection : projectConnections.getFunctionConnections())
        for (auto it = connection._number_of_function_calls.begin(); it != connection._number_of_function_calls.end(); ++it)
            for (auto connection2 : projectConnections.getFunctionConnections())
                if (connection2._function_name == it->first && connection._namespace != connection2._namespace
                    && connection._namespace != "empty" && connection2._namespace != "empty")
                    std::cout << connection._namespace << " is connected with " << connection2._namespace <<
                    " because " << it->first << " calls " << connection2._function_name << std::endl;

}
