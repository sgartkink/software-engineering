#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>

int x = 150;
int y = 50;
class paradigmID {
public:
	std::string filename;
	std::string fileID;
    int X = x;
    int Y = y;
    int c = 1;
    int v = 1;
    paradigmID(const std::string &s1 = " ", const std::string &i = " ") : filename(s1), fileID(i) {}
};

std::map<std::string, int> filesID;
std::map<int, std::vector<int>> IDmap;
std::vector<paradigmID> Vec;
void files_graph(std::string file_name, std::list<std::string> files_list, our_map map) {
    
    std::stringstream name, name2;
    std::string s, s2, name3, name4, id;
    int usecaseid = 1, i = 0;
    //int cntr = 1;
    
    
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
        i++;
    }
    paradigmID plik[i + 1];
    
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
        name << *it;
        s = name.str();
        name3 = getname(s);
        filesID[name3] = usecaseid;
        id = "id";
        id += std::to_string(usecaseid);
        plik[usecaseid].fileID = id;
        plik[usecaseid].filename = name3;
        usecaseid++;
    }
    usecaseid = 1;
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
        for (auto const& include : map[*it].includes) {
            name2 << include;
            s2 = name2.str();
            name4 = getname(s2);
            IDmap[usecaseid].push_back(filesID.find(name4)->second);
        }
        usecaseid++;
    }

    for (auto const& x : IDmap) {
        std::cout << x.first << ":" << std::endl;
        for (int i = 0; i < x.second.size(); i++)
            std::cout << x.second[i] << std::endl;
    }
    for (auto const& x : filesID) {
        std::cout << x.first << ":" << x.second << std::endl;
        
    }
    
    int ZOrder = 2;
    
   /* paradigmID plik1("Test",id);
    cntr++;
    id = "id";
    id += std::to_string(cntr);
    paradigmID plik2("Test2",id); */
    
    
    std::ifstream fi, fi2, fi3, fi4, fi5;
    std::ofstream fo;
    fi.open("base.txt");
    fi2.open("base2.txt");
    fi3.open("base3.txt");
    fi4.open("base4.txt");
    fi5.open("base5.txt");
    fo.open("diagram.xml");
    std::string str;
    
    while(std::getline(fi, str))
    {
        fo<<str;
    }
    
    fo << "\n";
    
    
    fo << "<Include From=" << '"' << plik[1].fileID << '"' << " Id=" << '"' << plik[1].fileID << "c" << plik[1].c << '"' << " Name=" << '"' << 1 << '"' << " To=" << '"' << plik[2].fileID << '"' << "><MasterView><Include Idref=" << '"' << plik[1].fileID << "v" << plik[1].v << '"' << " Name=" << '"' << 1 << '"' << "/></MasterView></Include>";
    plik[1].v++;
    plik[1].c++;
    y += 100;
    plik[2].Y += y;

       // fo <<"include..."; - for includes
    
    while(std::getline(fi2, str))
    {
        fo<<str;
    }
    

    fo << "\n<UseCase Id=" << '"' << plik[1].fileID << '"' << " Name=" << '"' << plik[1].filename << '"' << ">" <<
    "\n</UseCase>";
    fo << "\n<UseCase Id=" << '"' << plik[2].fileID << '"' << " Name=" << '"' << plik[2].filename << '"' << ">" <<
    "\n</UseCase>";
    
    fo << "</Models>\n<Diagrams>\n";
    
    while(std::getline(fi3, str))
       {
           fo<<str;
       }
    
    fo << "\n";
    
    plik[1].c = 1;
    plik[1].v = 1;
    
    fo << "<Include Id=" << '"' << plik[1].fileID << "v" << plik[1].v << '"' << " MetaModelElement=" << '"' << plik[1].fileID << "c" << plik[1].c << '"' << " Model=" << '"' << plik[1].fileID << "c" << plik[1].c << '"' << " ZOrder=" << '"' << ZOrder << '"' << " To=" << '"' << plik[2].fileID << "s" << '"' << " ";
    while(std::getline(fi5, str))
          {
              fo<<str;
          }
    ZOrder += 2;
    fi5.clear();
    fi5.seekg(0);
    
    fo << " X=" << '"' <<  plik[1].X + (plik[2].X - plik[1].X)/2 << '"' << " Y=" << '"' << plik[1].Y + (plik[2].Y - plik[1].Y)/2 << '"' << "/></Include>";
    
     // fo <<"include..."; - for includes x2
    
    fo << "</Connectors><Shapes>";
    
    
    fo << "\n<UseCase Id=" << '"' << plik[1].fileID << "s" << '"' << " MetaModelElement=" << '"' << plik[1].fileID << '"' << " Model=" << '"' << plik[1].fileID << '"' << " Name=" << '"' << plik[1].filename << '"' <<" X=" << '"' << plik[1].X << '"' << " Y=" << '"' << plik[1].Y << '"' <<" ZOrder=" << '"' << ZOrder << '"' << " ";
    while(std::getline(fi4, str))
          {
              fo<<str;
          }
    ZOrder += 2;
    fi4.clear();
    fi4.seekg(0);
    
   fo << "\n<UseCase Id=" << '"' << plik[2].fileID << "s" << '"' << " MetaModelElement=" << '"' << plik[2].fileID << '"' << " Model=" << '"' << plik[2].fileID << '"' << " Name=" << '"' << plik[2].filename << '"' <<" X=" << '"' << plik[2].X << '"' << " Y=" << '"' << plik[2].Y << '"' <<" ZOrder=" << '"' << ZOrder << '"' << " ";
    while(std::getline(fi4, str))
          {
              fo<<str;
          }
    ZOrder += 2;
    fi4.clear();
    fi4.seekg(0);
    
    
    
    fo << "</Shapes></UseCaseDiagram></Diagrams></Project>";
    
    fi.close();
    fi2.close();
    fi3.close();
    fi4.close();
    fi5.close();
    fo.close();
}
