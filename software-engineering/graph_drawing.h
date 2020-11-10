#include <fstream>
#include <string>
#include <sstream>
#include "structs/ProjectConnections.h"

void bash_files(std::string graph_name) {
    std::string png_name = graph_name + ".png";
    std::string gv_name = graph_name + ".gv";
#ifdef _WIN32
    std::string bat_name = graph_name + ".bat";
    std::ofstream script(bat_name);
    script << "@ECHO OFF\n";
    script << "dot -Tpng " << gv_name << " -o " << png_name;
    script.close();
    system((bat_name).c_str());
    system((png_name).c_str());
#elif unix || APPLE
    std::string sh_name = graph_name + ".sh";
    std::ofstream script(sh_name);
    script << "#/bin/bash\n";
    script << "dot -Tpng " << gv_name << " -o " png_name;
    script.close();
    system((sh_name).c_str());
    system((png_name).c_str());
#endif
}
void making_files_graph(std::string graph_name, std::list<std::string> files_list, search::our_map map) {
    std::string x = graph_name + ".gv";
    std::ofstream file(x);
    std::stringstream name, name2;
    std::string s, s2;

    file << "digraph files_graph\n{\n";
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
        for (auto const& include : map[*it].includes) {
            name << *it;
            s = name.str();
            name2 << include;
            s2 = name2.str();
            //file << '"' << getname(s) << "_" << map[*it].size << "b" << '"' << "->" << '"' << include << '"' << "[label = 1];" << "\n";
            file << '"' << getname(s) << '"' << "->" << '"' << getname(s2) << '"' << "[label = 1];" << "\n";
        }
    }
    file << "}";
    file.close();
    bash_files(graph_name);
}
void making_functions_graph(std::string graph_name, ProjectConnections projectConnections) {
    std::string x = graph_name + ".gv";
    std::ofstream file(x);
    file << "digraph connections_graph\n{\n";
    file.close();
    for (auto connection : projectConnections.getFunctionConnections()) {
        connection.connections_to_graph(x);
    }
    file.open(x, std::ios::out | std::ios::app);
    file << "}";
    file.close();
    bash_files(graph_name);
}
void making_namespaces_graph(std::string graph_name, ProjectConnections projectConnections) {
    std::string x = graph_name + ".gv";
    std::ofstream file(x);
    file << "digraph connections_graph\n{\n";
    file.close();
    for (auto name : projectConnections.getNamespaceConnections()) {
        name.includes_to_graph(x);
    }
    file.open(x, std::ios::out | std::ios::app);
    file << "}";
    file.close();
    bash_files(graph_name);
}