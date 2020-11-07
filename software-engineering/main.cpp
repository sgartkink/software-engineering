#include <iostream>
#include "list_files.h"
#include "search.h"
#include "check_connections.h"

int main()
{
    const std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());
    //const std::list<std::string> files_list = list_files::get_list_files("/home/szymon/git/software-engineering/software-engineering/");

    search::our_map map = search::create_map(files_list);

    for (auto it = files_list.begin(); it != files_list.end(); ++it)
    {
        std::cout << *it << std::endl;
        std::cout << "includes: ";

        for (auto const& include : map[*it].includes)
        {
            std::cout << include << " ";
        }

        std::cout << std::endl;
        std::cout << "file size: " << map[*it].size << " b" << std::endl << std::endl;
    }

	class ProjectConnections
    {
        std::vector<function_connections> connections;
        std::vector<namespace_connections> namespaces;

    public:
    	ProjectConnections(const std::list<std::string> files_list)
    	{
            check_connections(files_list, connections, namespaces);
    	}

        std::vector<function_connections> getFunctionConnections()
    	{
            return connections;
    	}

        std::vector<namespace_connections> getNamespaceConnections()
        {
            return namespaces;
        }
    };

    ProjectConnections projectConnections(files_list);
    

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

    return 0;
}
