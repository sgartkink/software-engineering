#include <filesystem>

int filesize(const std::string &filename) {
    return std::filesystem::file_size  (filename);
}
