#include <list>
#include <filesystem>

#define BOOST_TEST_MODULE list_files_tests
#include <boost/test/included/unit_test.hpp>

namespace ends {

bool ends_with(const std::string& str, const std::string& suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size() - suffix.size(), suffix.size(), suffix);
}

}//~namespace ends

namespace list_files {

std::list<std::string> get_list_files(const std::string &path)
{
    std::list<std::string> list;

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path))
    {
        const std::string file_path = dirEntry.path().string();

        if (ends::ends_with(file_path, ".h") || ends::ends_with(file_path, ".cpp"))
            list.push_back(dirEntry.path().string());
    }

    return list;
}

BOOST_AUTO_TEST_CASE( list_files_tests )
{
    std::string str = "test.cpp", str2 = "test.h", str3 = "test.abcd", str4 = "test.test", str5 = "t";
    std::string suf = ".cpp", suf2 = ".h", suf3 = ".abcd", suf4 = "tset", suf5 = "test";
    BOOST_CHECK ( ends::ends_with(str, suf));
    BOOST_CHECK ( ends::ends_with(str2, suf2));
    BOOST_CHECK ( ends::ends_with(str3, suf3));
    BOOST_CHECK ( ends::ends_with(str4, suf4) == false);
    BOOST_CHECK ( ends::ends_with(str5, suf5) == false);

    const std::string path = std::filesystem::current_path().string();
    const std::list<std::string> files_list = list_files::get_list_files(path);
    std::list<std::string> list;

    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator(path))
    {
        const std::string file_path = dirEntry.path().string();

        if (ends::ends_with(file_path, ".h") || ends::ends_with(file_path, ".cpp"))
            list.push_back(dirEntry.path().string());
    }

    BOOST_TEST (files_list == list);
}

}//~namespace list_files
