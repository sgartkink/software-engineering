
#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<list>
#include<string>

struct file_struct {
    std::vector<std::string> includes;
    int size;
};

typedef std::map<std::string, file_struct> our_map;

our_map create_map(std::list<std::string> list_files)
{
    our_map map;

    for (auto it = list_files.begin(); it != list_files.end(); ++it)
    {
        std::ifstream file;
        file.open(*it);

        if (file.fail())
        {
            file.close();
            std::cout << "couldn't open file: " << *it;
            continue;
        }

        while (!file.eof())
        {

           // std::string file_included;
           // map[*it].includes.push_back(file_included);
            
            
            std::string line;
            getline(file, line);
            
            std::string search = "#include";
            std::size_t where = line.find(search);
            
            if(where != std::string::npos){
                where += search.size();
                std::string file_name = line.substr(where);
                
                
                map[*it].includes.push_back(file_name);
                
        }
    }

}
    
    return map;
}

