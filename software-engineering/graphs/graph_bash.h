#include <string>

void bash_files(std::string graph_name) {
    std::string png_name = graph_name + ".png";
    std::string gv_name = graph_name + ".gv";
#ifdef _WIN32
    std::string script_name = graph_name + ".bat";
#elif unix || APPLE
    std::string script_name = graph_name + ".sh";
#endif
    std::ofstream script(script_name);
    script << "@ECHO OFF\n";
    script << "dot -Tpng " << gv_name << " -o " << png_name;
    script.close();
    system((script_name).c_str());
    system((png_name).c_str());
}
