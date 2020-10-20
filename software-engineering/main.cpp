#include <iostream>

#include "list_files.h"
#include "get_sizes.h"

int main()
{
    std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path().string());

    std::list<int> sizes_list = file_size::get_sizes(files_list);

    /*for (auto const& i : files_list)
    {
        std::cout << i << std::endl;
    }

    for (auto const& i : sizes_list)
    {
        std::cout << i << std::endl;
    }*/
	
    return 0;
}