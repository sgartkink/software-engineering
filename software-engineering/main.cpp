#include <iostream>

#include "list_files.h"
#include "search.h"

int main()
{
    
    std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());

    our_map map = create_map(files_list);
	
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
	
    return 0;
}