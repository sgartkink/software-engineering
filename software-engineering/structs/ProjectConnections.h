#pragma once
#include <vector>

#include "../functions/check_connections.h"
#include "FunctionConnections.h"

class ProjectConnections
{
    std::vector<FunctionConnections> connections;
    std::vector<NamespaceConnections> namespaces;

public:
    ProjectConnections(const std::list<std::string> files_list)
    {
        check_connections(files_list, connections, namespaces);
    }

    std::vector<FunctionConnections> getFunctionConnections()
    {
        return connections;
    }

    std::vector<NamespaceConnections> getNamespaceConnections()
    {
        return namespaces;
    }
};
