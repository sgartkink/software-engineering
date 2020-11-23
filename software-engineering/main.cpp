#include "functions/create_functions_file.h"
#include "functions/list_files.h"
#include "functions/search.h"
#include "functions/display_connections.h"
#include "structs/ProjectConnections.h"
#include "graph_drawing.h"

int main()
{
    const std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());

    search::our_map map = search::create_map(files_list);

    making_files_graph("files_graph", files_list, map);

    ProjectConnections projectConnections(files_list);

    making_functions_graph("functions_graph", projectConnections);

    making_namespaces_graph("namespaces_graph", projectConnections);

    display_connections(projectConnections);

    create_functions_file(projectConnections.getFunctionConnections()); // functions to file
	
    return 0;
}
