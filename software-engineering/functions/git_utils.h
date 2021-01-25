#ifndef GIT_UTILS_H
#define GIT_UTILS_H

#include <iostream>
#include <array>
#include <memory>
#include <forward_list>

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

static std::forward_list<std::string> changed_files_list(std::string path = "")
{
    std::forward_list<std::string> list;
    std::array<char, 128> buffer;
    std::string result;
    std::string command;
    if (path.empty())
        command = "git diff --name-only HEAD~1 HEAD";
    else
        command = "cd " + path + "; git diff --name-only HEAD~1 HEAD";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
        return list;
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    std::string delimiter = "\n";
    size_t pos = 0;
    std::string token;
    while ((pos = result.find(delimiter)) != std::string::npos) {
        std::string substr = result.substr(0, pos);
        list.push_front(substr);
        result.erase(0, pos + delimiter.length());
    }

    return list;
}

#endif // GIT_UTILS_H
