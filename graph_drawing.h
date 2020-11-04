#include <fstream>
#include <string>


void making_files_graph(std::string graph_name, std::list<std::string> files_list, our_map map) {
	std::ofstream grapg_name("files_graph.gv");
    grapg_name << "digraph files_graph\n{\n";
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
            for (auto const& include : map[*it].includes) {
                grapg_name << '"' << *it << "_" << map[*it].size << "b" << '"' << "->" << '"' << include << '"' << "[label = 1]"<<"\n";

            }
    }
    grapg_name << "}";
    grapg_name.close();
    //for Windows
    std::ofstream script("files_graph.bat");
    script << "@ECHO OFF\n";
    script << "dot -Tpng files_graph.gv -o files_graph.png";
    script.close();
    system("files_graph.bat");
    system("files_graph.png");

    //for Linux
    /*
    std::ofstream script("files_graph.sh");
    script << "#/bin/bash\n";
    script << "dot -Tpng files_graph.gv -o files_graph.png";
    script.close();
    system("files_graph.sh");
    system("files_graph.png");
    */
}
