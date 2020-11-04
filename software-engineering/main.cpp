#include <iostream>
#include <regex>

#include "list_files.h"
#include "search.h"
#include "check_connections.h"

int main()
{
    const std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());

    search::our_map map = search::create_map(files_list);

    for (auto it = files_list.begin(); it != files_list.end(); ++it)
    {
        std::cout << *it << std::endl;
        std::cout << "includes: ";
    	
        for (auto const& include : map[*it].includes)
        {
            std::cout << include << " ";
        }
    	
        std::cout << std::endl;
        std::cout << "file size: " << map[*it].size << " b" << std::endl << std::endl;
    }

    std::list<function_struct> function_list;

    check_connections(files_list, &function_list);

    std::cout << std::endl << std::endl << "Functions: " << std::endl;
	
    for (auto const& i : function_list) {
		if(i.function_name.length()!=0)
			std::cout << i.function_name << std::endl;
    	
        for (auto const& k : i.inside_function_names) {
            std::cout << "  " + k << std::endl;
        }
    }
	
    return 0;
}
