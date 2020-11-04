#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include "file_size.h"

namespace search
{
    struct file_struct {
        std::vector<std::string> includes;
        int size;
    };

    typedef std::map<std::string, file_struct> our_map;

    our_map create_map(std::list<std::string> list_files)
    {
        our_map map;

        for (auto it = list_files.begin(); it != list_files.end(); ++it)
        {
            std::ifstream file;
            file.open(*it);

            if (file.fail())
            {
                file.close();
                std::cout << "couldn't open file: " << *it;
                continue;
            }

            // file size
            map[*it].size = file_size::filesize(*it);

            while (!file.eof())
            {
                std::string line;
                getline(file, line);

                std::string search = "#include";
                std::size_t where = line.find(search);
                std::size_t is_library = line.find("<");

                if (where != std::string::npos && is_library == std::string::npos)
                {
                    where += search.size();
                    auto file_name = line.substr(where);

                    // trim string of spaces and quotes
                    file_name.erase(std::remove(std::begin(file_name), std::end(file_name), ' '), std::end(file_name));
                    file_name.erase(std::remove(std::begin(file_name), std::end(file_name), '"'), std::end(file_name));

                    // check if string is a name of a header or cpp file
                    if (line.find(".h") != std::string::npos || line.find(".cpp") != std::string::npos)
                        map[*it].includes.push_back(file_name);
                }
            }
        }

        return map;
    }
}


