#include <filesystem>

int filesize(std::string filename)
{
    return std::filesystem::file_size(filename);
}
