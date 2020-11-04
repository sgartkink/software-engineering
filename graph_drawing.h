#include <fstream>
#include <string>


void making_files_graph(std::string graph_name, std::list<std::string> files_list, our_map map) {
	std::ofstream grapg_name("graph.gv");
    grapg_name << "digraph files\n{\n";
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
            for (auto const& include : map[*it].includes) {
                grapg_name << *it <<" " << map[*it].size << "b" << "->" << include << "\n";
            }
    }
    grapg_name << "}";
    grapg_name.close();


}
