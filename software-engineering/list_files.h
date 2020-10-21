#pragma once
#include <iostream>
#include <list>
#include <filesystem>

namespace list_files {

    bool ends_with(const std::string& str, const std::string& suffix)
    {
        return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
    }

    std::list<std::string> get_list_files(std::string path)
    {
        std::list<std::string> list;

        for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path))
        {
            const std::string file_path = dirEntry.path().string();

            if (ends_with(file_path, ".h") || ends_with(file_path, ".cpp"))
                list.push_back(dirEntry.path().string());
        }

        return list;
    }


}