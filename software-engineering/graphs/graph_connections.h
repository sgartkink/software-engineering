#include <string>
#include <sstream>
#include <fstream>

#include "../structs/FileStruct.h"

std::string getname(std::string s) {
    unsigned long n = s.length();
    char* tab = NULL;
    int i = 0;
    tab = new char[n + 1];
    for (int j = 0; j <= n; j++)
        tab[j] = 0;
    std::string a = "";
    s.copy(tab, s.size());
    tab[s.size()] = '\0';

    while (tab[n] != 47 && tab[n] != 92) {
        a += tab[n];
        if (tab[n - 3] == 46 && tab[n - 2] == 104) {
            a += tab[n - 1];
            break;
        }
        n--;
    }
    n = a.length();
    for (i = 0; i < n / 2; i++)
        std::swap(a[i], a[n - i - 1]);
    int x = a.length();
    a.erase((x - 1), 1);
    tab = NULL;
    return a;
}

void files_graph(std::string file_name, std::list<std::string> files_list, std::map<std::string, FileStruct> map) {
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::app);
    std::stringstream name, name2;
    std::string s, s2;
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
        for (auto const& include : map[*it].includes) {
            name << *it;
            s = name.str();
            name2 << include;
            s2 = name2.str();
            //file << '"' << getname(s) << "_" << map[*it].size << "b" << '"' << "->" << '"' << include << '"' << "[label = 1];" << "\n";
            file << '"' << getname(s) << '"' << "->" << '"' << getname(s2) << '"' << " [label = 1];\n" << '"' << getname(s) << '"' << " [shape = box];\n" << '"' << getname(s2) << '"' << " [shape = box];\n";
        }
    }
    file.close();
}
void functions_graph(std::string file_name, ProjectConnections projectConnections, std::vector<std::string> functions_list = {}) {
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::app);
    for (auto connection : projectConnections.getFunctionConnections()) {
        connection.connections_to_graph(file_name);
    }
    file.close();
}
void namespaces_graph(std::string file_name, ProjectConnections projectConnections) {
    std::ofstream file;
    file.open(file_name, std::ios::out | std::ios::app);
    for (auto connection : projectConnections.getFunctionConnections())
        for (auto it = connection._number_of_function_calls.begin(); it != connection._number_of_function_calls.end(); ++it)
            for (auto connection2 : projectConnections.getFunctionConnections())
                if (connection2._function_name == it->first && connection._namespace != connection2._namespace
                    && connection._namespace != "empty" && connection2._namespace != "empty") {
                    file <<  "edge [color=blue];\n";
                    file << '"' << connection._namespace << '"' << "->" << '"' << connection2._namespace << '"'
                        << "[label = 1];\n" << '"' << connection._namespace << '"' << " [shape = hexagon];\n" << '"' << connection2._namespace << '"' << " [shape = hexagon];\n";
                }
    file.close();
}
