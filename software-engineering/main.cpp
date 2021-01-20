#include "functions/list_files.h"
#include "functions/search.h"
#include "functions/display_connections.h"
#include "structs/ProjectConnections.h"
#include "graphs/graph_drawing.h"
#include "paradigm_graph.h"

#define BOOST_TEST_MODULE main_tests
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE( main_tests )
{
    const std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());
    search::our_map map = search::create_map(files_list);

    ProjectConnections projectConnections(files_list);
    files_graph("diagram.xml", files_list, map);

    int number;

    do {
        std::cout << "Choose what do you want to see:\n1) Files graph\n2) Functions graph\n3) Namespaces graph\n4) Files and functions relationship graph\n5) Graphs export to Visual Paradigm\n0) Exit\n";

        std::cin >> number;
        std::cout << std::endl;

        if (number != 0)
            general_graph(number, files_list, map, projectConnections);
    } while (number != 0);
}
