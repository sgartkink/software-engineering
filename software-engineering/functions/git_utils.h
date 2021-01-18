#ifndef GIT_UTILS_H
#define GIT_UTILS_H

#include <iostream>
#include <array>
#include <memory>

static std::string get_last_commit_id(std::string file, std::string path = "")
{
    std::array<char, 128> buffer;
    std::string result;
    std::string command;
    if (path.empty())
        command = "git log --pretty=oneline " + file;
    else
        command = "cd " + path + "; git log --pretty=oneline " + file;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
        break;
    }
    if (result.find(' ') == std::string::npos)
        return "";
    return result.substr(0, result.find(' '));
}

static std::string get_first_commit_id(std::string file, std::string path = "")
{
    std::array<char, 128> buffer;
    std::string result;
    std::string command;
    if (path.empty())
        command = "git log --pretty=oneline " + file;
    else
        command = "cd " + path + "; git log --pretty=oneline " + file;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
        return "";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    if (result.rfind('\n', result.size() - 2) == std::string::npos)
        return "";

    result = result.substr(result.rfind('\n', result.size() - 2));

    if (result.find(' ') == std::string::npos)
        return "";

    return result.substr(0, result.find(' '));
}

#endif // GIT_UTILS_H
