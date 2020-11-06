#include <iostream>
#include "list_files.h"
#include "search.h"
#include "check_connections.h"

int main()
{
    const std::list<std::string> files_list = list_files::get_list_files("/home/szymon/git/software-engineering/software-engineering/");

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

    std::vector<function_connections> connections;
    std::vector<namespace_connections> namespaces;
    check_connections(files_list, connections, namespaces);

    for (auto connection : connections)
        connection.show_connections();

    for (auto name : namespaces)
        name.show_included_function();

    return 0;
}
