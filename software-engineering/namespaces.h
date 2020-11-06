//#pragma once
//// // namespace declaration when { in next line and is not a comment
//if (previous_line.find("namespace") != std::string::npos && line.find("{") != std::string::npos && !check_if_comment(previous_line))
//{
//    int i = previous_line.find("namespace") + 9;
//    bool break_out = false;     // break out if after name of the namespace 
//    for (; i < previous_line.length(); ++i)
//    {
//        if (previous_line.at(i) != '{' && previous_line.at(i) != ' ') break_out = true;
//        if (previous_line.at(i) == '{' || previous_line.at(i) == ' ')
//            break;
//    }
//
//    for (int i = 0; i < line.length(); ++i) //check if line is not just a function, class, template or struct
//    {
//        if (line.at(i) == '(' || line.at(i) == '<') break_out = true;
//    }
//    if (line.find("class") != std::string::npos || line.find("struct") != std::string::npos) break_out = true;
//
//    if (!break_out)
//    {
//        std::string temp;
//        temp = previous_line.substr(i, previous_line.length() - i);
//        temp = strip_of_spaces(temp);
//        if (check_if_namespace_is_valid(temp))
//        {
//            namespace_name = temp;
//            std::cout << std::endl << "Namespace: " << namespace_name << std::endl;
//
//            is_in_namespace = true;
//        }
//    }
//}
//
//// namespace declaration when { in the same line and is not a comment
//else if (line.find("namespace") != std::string::npos && line.find("{") != std::string::npos && !check_if_comment(line))
//{
//    int i = line.find("namespace") + 9;
//    bool break_out = false;
//
//    for (; i < line.length(); ++i)
//    {
//        if (line.at(i) != '{' && line.at(i) != ' ') break_out = true;
//        if (line.at(i) == '{' || line.at(i) == ' ')
//            break;
//    }
//
//    if (!break_out)
//    {
//        std::string temp;
//        temp = line.substr(i, line.length() - i);
//        temp = strip_of_spaces(temp);
//        if (check_if_namespace_is_valid(temp))
//        {
//            namespace_name = temp;
//            std::cout << std::endl << "Namespace: " << namespace_name << std::endl;
//
//            is_in_namespace = true;
//        }
//    }
//}
//
//// decrement or increment bracket_count if found bracket, prevent artifical incrementing
//if (line.find("{") != std::string::npos && !check_if_comment(line) && is_in_namespace && line.find('"{"') == std::string::npos && line.find("'{'") == std::string::npos)
//{
//    bracket_counter++;
//}
//
//if (line.find("}") != std::string::npos && !check_if_comment(line) && is_in_namespace && line.find('"}"') == std::string::npos && line.find("'}'") == std::string::npos)
//{
//    bracket_counter--;
//}
//
//// check if still in namespace
//if (line.find("}") != std::string::npos && !check_if_comment(line) && is_in_namespace)
//{
//    if (bracket_counter == 0)
//    {
//        is_in_namespace = false;
//        std::cout << std::endl << "End of namespace: " << namespace_name << std::endl;
//    }
//}