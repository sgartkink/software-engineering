#include <iostream>

#include "list_files.h"

int main()
{
    std::list<std::string> files_list = list_files::get_list_files(std::filesystem::current_path());

    return 0;
}
