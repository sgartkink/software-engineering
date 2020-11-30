#include "functions/create_functions_file.h"
#include "functions/list_files.h"
#include "functions/search.h"
#include "functions/display_connections.h"
#include "structs/ProjectConnections.h"
#include "graphs/graph_drawing.h"


int main()
{

    const std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());

    search::our_map map = search::create_map(files_list);

    ProjectConnections projectConnections(files_list);

    int number;

    do {
        std::cout << "Choose what do you want to see:\n1) Files graph\n2) Functions graph\n3) Namespaces graph\n4) Files and functions relationship graph\n5) Graphs export to Visual Paradigm\n0) Exit\n";

        std::cin >> number;
        std::cout << std::endl;

        if (number != 0)
            general_graph(number, files_list, map, projectConnections);
    } while (number != 0);

    return 0;
}
