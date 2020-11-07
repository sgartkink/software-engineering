#pragma once
#include <string>

bool should_increment(std::string substring, int i)
{
    if (substring.at(i) == ' ' || substring.at(i) == ':' || substring.at(i) == '.'
        || substring.at(i) == '>' || substring.at(i) == '=' || substring.at(i) == '('
        || substring.at(i) == '"' || substring.at(i) == '\'' || substring.at(i) == ']'
        || substring.at(i) == ';' || substring.at(i) == '+' || substring.at(i) == '-'
        || substring.at(i) == '!' || substring.at(i) == '%' || substring.at(i) == '^'
        || substring.at(i) == '&' || substring.at(i) == '*' || substring.at(i) == '|'
        || substring.at(i) == '?') return true;
    return false;
}
