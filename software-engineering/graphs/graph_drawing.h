
#include "../structs/FileStruct.h"
#include "./graph_connections.h"
#include "./graph_includes.h"
#include "./graph_bash.h"




void general_graph(int number, std::list<std::string> files_list, std::map<std::string, FileStruct> map, ProjectConnections projectConnections) {
    
    std::string graph_name = "general_graph";
    std::string x = graph_name + ".gv";
    std::ofstream file(x);
    bool created = 1;
    
    if (number == 1) {
        file << "digraph files_graph\n{\nsubgraph cluster0\n{\nnode[style = filled,color = white];\nstyle = filled;\n\color = lightgrey;\n";
        file.close();
        files_graph(x, files_list, map);
        file.open(x, std::ios::out | std::ios::app);
        file << "label = " << '"' << "Files graph" << '"' << ";\n}\n}";
        file.close();
    }
    else if (number == 2) {
        file << "digraph files_graph\n{\nsubgraph cluster0\n{\nnode[style = filled,color = white];\nstyle = filled;\n\color = lightgrey;\n";
        file.close();
        //std::vector<std::string> functions_list = our_funtions_list(projectConnections.getFunctionConnections());
        funtions_files_to_graph(projectConnections.getFunctionConnections(), x);
        functions_graph(x, projectConnections);
        //functions_graph(x, projectConnections, functions_list);
        file.open(x, std::ios::out | std::ios::app);
        file << "label = " << '"' << "Functions graph" << '"' << ";\n}\n}";
        file.close();
    }
    else if (number == 3) {
        file << "digraph files_graph\n{\nsubgraph cluster0\n{\nnode[style = filled,color = white];\nstyle = filled;\n\color = lightgrey;\n";
        file.close();
        namespaces_graph(x, projectConnections);
        file.open(x, std::ios::out | std::ios::app);
        file << "label = " << '"' << "Namespaces graph" << '"' << ";\n}\n}";
        file.close();
        created = 1;
    }
    else if (number == 12 || number == 21) {
        file << "digraph " << graph_name << "\n{\n";
        file.close();
        //std::vector<std::string> functions_list = funtions_files_to_graph(projectConnections.getFunctionConnections(), x);
        //functions_graph(x, projectConnections, functions_list);
        funtions_files_to_graph(projectConnections.getFunctionConnections(), x);
        functions_graph(x, projectConnections);
        file.open(x, std::ios::out | std::ios::app);
        file << "}";
        file.close();
    }
    else if (number == 13 || number == 31) {
        file << "digraph " << graph_name << "\n{\n";
        file.close();
        namespaces_files_to_graph(projectConnections.getNamespaceConnections(), x);
        files_graph(x, files_list, map);
        namespaces_graph(x, projectConnections);
        file.open(x, std::ios::out | std::ios::app);
        file << "label = " << '"' << graph_name << '"' << ";\n}";
        file.close();
    }
    else if (number == 23 || number == 32) {
        file << "digraph " << graph_name << "\n{\n";
        file.close();
        for (auto name : projectConnections.getNamespaceConnections()) {
            name.functions_namespaces_to_graph(x);
        }
        functions_graph(x, projectConnections);
        file.open(x, std::ios::out | std::ios::app);
        file << "}";
        file.close();
    }
    else if (number == 123 || number == 132 || number == 213 || number == 231 || number == 312 || number == 321) {
        file << "digraph " << graph_name << "\n{\n";
        file.close();
        funtions_files_to_graph(projectConnections.getFunctionConnections(), x);
        namespaces_files_to_graph2(projectConnections.getNamespaceConnections(), x);
        for (auto name : projectConnections.getNamespaceConnections()) {
            name.functions_namespaces_to_graph(x);
        }
        functions_graph(x, projectConnections);
        file.open(x, std::ios::out | std::ios::app);
        file << "}";
        file.close();
    }
    else if (number == 4) {
        file << "digraph " << graph_name << "\n{\n";
        file.close();
        funtions_files_to_graph(projectConnections.getFunctionConnections(), x, "reversed");
        file.open(x, std::ios::out | std::ios::app);
        file << "}";
        file.close();
    }
    else {
        std::cout << "You entered wrong number\n\n";
        created = 0;
    }
    if(created == 1)
        bash_files(graph_name);
}

