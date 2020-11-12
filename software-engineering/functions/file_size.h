#pragma once
#include <filesystem>

namespace file_size {

    int filesize(const std::string& filename) {
        return std::filesystem::file_size(filename);
    }

}

