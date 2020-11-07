#pragma once
#include <iostream>
#include <list>
#include "search.h"

void display_includes(std::list<std::string> files_list, search::our_map map)
{
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
}
