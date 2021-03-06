#include <vector>
#include "../structs/FunctionConnections.h"
#include "../structs/ProjectConnections.h"


/*std::vector<std::string> */  void funtions_files_to_graph(std::vector<FunctionConnections> connections, std::string file_name, std::string arrow = "normal")
{
    std::vector<std::string> shown_filenames;
    //std::vector<std::string> functions_list;
    std::ofstream file;
    static int cluster = 0;
    file.open(file_name, std::ios::out | std::ios::app);

    bool firstBracket = true;

    for (auto connection : connections) {
        std::size_t found = connection.get_file_name().find_last_of("\\");
        std::string function_name = connection.get_function_name();
        std::string file_name = connection.get_file_name().substr(found + 1, connection.get_file_name().length());

        std::vector<std::string>::iterator it;
        it = std::find(shown_filenames.begin(), shown_filenames.end(), file_name);
        if (it == shown_filenames.end()) {
            if (firstBracket) firstBracket = false;
            else file << "}";
            file << "\nsubgraph cluster" << cluster << "\n{\nnode[style = filled,color = white];\nstyle = filled;\ncolor = lightgrey;\n" << '"' << file_name << '"' << " [shape = box];\n";
            shown_filenames.push_back(file_name);
            ++cluster;
        }
        //functions_list.push_back(function_name);
        if(arrow == "normal")
            file << '"' << file_name << '"' << "->" << '"' << function_name << '"' << "\n";
        else
            file << '"' << function_name << '"' << "->" << '"' << file_name << '"' << "\n";
    }

    file << "}";

    file.close();

    //return functions_list;
}

std::vector<std::string> our_funtions_list(std::vector<FunctionConnections> connections)
{
    std::vector<std::string> shown_filenames;
    std::vector<std::string> functions_list;

    for (auto connection : connections) {
        std::size_t found = connection.get_file_name().find_last_of("\\");
        std::string function_name = connection.get_function_name();
        std::string file_name = connection.get_file_name().substr(found + 1, connection.get_file_name().length());

        std::vector<std::string>::iterator it;
        it = std::find(shown_filenames.begin(), shown_filenames.end(), file_name);
        if (it == shown_filenames.end()) {
            shown_filenames.push_back(file_name);
        }
        functions_list.push_back(function_name);
    }
    return functions_list;
}

void namespaces_files_to_graph(std::vector<NamespaceConnections> connections, std::string file_name) {
    std::vector<std::string> shown_filenames;
    std::ofstream file;
    static int cluster = 0;
    file.open(file_name, std::ofstream::out | std::ofstream::app);

    bool firstBracket = true;

    for (auto connection : connections) {
        std::size_t found = connection.get_file_name().find_last_of("\\");
        std::string namespace_name = connection.get_namespace_name();
        std::string file_name = connection.get_file_name().substr(found + 1, connection.get_file_name().length());

        std::vector<std::string>::iterator it;
        it = std::find(shown_filenames.begin(), shown_filenames.end(), file_name);

        if (it == shown_filenames.end()) {
            if (firstBracket) firstBracket = false;
            else file << "}";
            file << "\nsubgraph cluster" << cluster << "\n{\nnode[style = filled,color = white];\nstyle = filled;\ncolor = lightgrey;\n" << '"' << file_name << '"' << " [shape = box];\n";
            shown_filenames.push_back(file_name);
            ++cluster;
        }
        file << "edge [color=violet];\n";
        file << '"' << file_name << '"' << "->" << '"' << namespace_name << '"' << "\n";
        file << '"' << namespace_name << '"' << " [shape = hexagon];\n";

    }
    file << "}\n";

    file.close();
}

void namespaces_files_to_graph2(std::vector<NamespaceConnections> connections, std::string file_name) {
    std::vector<std::string> shown_filenames;
    std::ofstream file;
    static int cluster = 0;
    file.open(file_name, std::ofstream::out | std::ofstream::app);

    bool firstBracket = true;

    for (auto connection : connections) {
        std::size_t found = connection.get_file_name().find_last_of("\\");
        std::string namespace_name = connection.get_namespace_name();
        std::string file_name = connection.get_file_name().substr(found + 1, connection.get_file_name().length());

        std::vector<std::string>::iterator it;
        it = std::find(shown_filenames.begin(), shown_filenames.end(), file_name);

        if (it == shown_filenames.end()) {
            if (firstBracket) firstBracket = false;
            else file << "}";
            file << "\nsubgraph cluster" << cluster << "\n{\nnode[style = filled,color = white];\nstyle = filled;\ncolor = lightgrey;\n" << '"' << file_name << '"' << " [shape = box];\n";
            shown_filenames.push_back(file_name);
            ++cluster;
        }
        file << "edge [color = darkviolet];\n";
        file << '"' << file_name << '"' << "->" << '"' << namespace_name << '"' << "\n";
        file << '"' << namespace_name << '"' << " [shape = hexagon];\n";
        connection.functions_namespaces_to_graph2(file_name);

    }
    file << "}\n";

    file.close();
}
