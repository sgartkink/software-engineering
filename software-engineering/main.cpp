#include "functions/list_files.h"
#include "functions/search.h"
#include "functions/display_connections.h"
#include "functions/display_includes.h"
#include "structs/ProjectConnections.h"

int main()
{
    const std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());
    //const std::list<std::string> files_list = list_files::get_list_files("/home/szymon/git/software-engineering/software-engineering/");

    search::our_map map = search::create_map(files_list);

    display_includes(files_list, map);

    ProjectConnections projectConnections(files_list);
    
    display_connections(projectConnections);
    
    return 0;
}
