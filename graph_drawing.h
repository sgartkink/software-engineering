#include <fstream>
#include <string>


void making_files_graph(std::string graph_name, std::list<std::string> files_list, our_map map) {
    std::string x = graph_name + ".gv";
	std::ofstream grapg_name(x);
    grapg_name << "digraph files_graph\n{\n";
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
            for (auto const& include : map[*it].includes) {
                grapg_name << '"' << *it << "_" << map[*it].size << "b" << '"' << "->" << '"' << include << '"' << "[label = 1]" << "\n";
            }
    }
    grapg_name << "}";
    grapg_name.close();
    #ifdef _WIN32
        std::ofstream script("files_graph.bat");
        script << "@ECHO OFF\n";
        script << "dot -Tpng " << x << " -o files_graph.png";
        script.close();
        system("files_graph.bat");
        system("files_graph.png");
    #else unix || APPLE
        std::ofstream script("files_graph.sh");
        script << "#/bin/bash\n";
        script << "dot -Tpng " << x << " -o files_graph.png";
        script.close();
        system("files_graph.sh");
        system("files_graph.png");
    #endif
}
