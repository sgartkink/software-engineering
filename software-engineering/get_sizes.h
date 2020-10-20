#pragma once
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace file_size {

    std::list<int> get_sizes(std::list<std::string> files_list)
    {
        std::list<int> sizes_list;

        for (auto const& i : files_list)
        {
            sizes_list.push_back(fs::file_size(i));

            //std::cout << fs::file_size(i) << std::endl;
        }

        return sizes_list;
    }
}