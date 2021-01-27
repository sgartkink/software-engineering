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
void paradigm_graph(std::string file_name, std::list<std::string> files_list, search::our_map map) {
    
    std::stringstream name, name2;
    std::string s, s2, name3, name4, id;
    int usecaseid = 1, i = 0;
    //int cntr = 1;
    
    
    for (auto it = files_list.begin(); it != files_list.end(); ++it) {
        i++;
    }
    paradigmID *plik = new paradigmID[i+1];
    
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
            if(filesID.find(name4)->second != 0)
            IDmap[usecaseid].push_back(filesID.find(name4)->second);
        }
        usecaseid++;
    }

    for (auto const& t : IDmap) {
        std::cout << t.first << ":" << std::endl;
        for (int i = 0; i < t.second.size(); i++)
            std::cout << t.second[i] << std::endl;
    }
    for (auto const& t : filesID) {
        std::cout << t.first << ":" << t.second << std::endl;
        
    }
    
    int ZOrder = 2;
    
   /* paradigmID plik1("Test",id);
    cntr++;
    id = "id";
    id += std::to_string(cntr);
    paradigmID plik2("Test2",id); */
    
    
    std::ifstream fi, fi2, fi3, fi4, fi5;
    std::ofstream fo;
    fi.open("bases/base.txt");
    fi2.open("bases/base2.txt");
    fi3.open("bases/base3.txt");
    fi4.open("bases/base4.txt");
    fi5.open("bases/base5.txt");
    fo.open("diagram.xml");
    std::string str;
    
    while(std::getline(fi, str))
    {
        fo<<str;
    }
    
    fo << "\n";
    
    int z, z2, k;
    for (auto const& t : IDmap) {
        z = t.first;
        y = plik[z].Y + 100;
        x = plik[z].X;
        for (int j = 0; j < t.second.size(); j++)
        {
            z2 = t.second[j];
    fo << "<Include From=" << '"' << plik[z].fileID << '"' << " Id=" << '"' << plik[z].fileID << "c" << plik[z].c << '"' << " Name=" << '"' << 1 << '"' << " To=" << '"' << plik[z2].fileID << '"' << "><MasterView><Include Idref=" << '"' << plik[z].fileID << "v" << plik[z].v << '"' << " Name=" << '"' << 1 << '"' << "/></MasterView></Include>";
            plik[z].v++;
            plik[z].c++;
            k = 1;
            for(int j = 1; j <= i; j++)
            {
                if(j == z2)
                    continue;
                if(abs(plik[j].X - x) < 15 && abs(plik[j].Y - y) < 15)
                    k = 0;
            }
            if(k == 0){
            plik[z2].Y = y + 100;
            plik[z2].X = x;
            }else
            {
            plik[z2].Y = y;
            plik[z2].X = x;
            }
            x += 180;
        }
    }
    
    /* fo << "<Include From=" << '"' << plik[1].fileID << '"' << " Id=" << '"' << plik[1].fileID << "c" << plik[1].c << '"' << " Name=" << '"' << 1 << '"' << " To=" << '"' << plik[2].fileID << '"' << "><MasterView><Include Idref=" << '"' << plik[1].fileID << "v" << plik[1].v << '"' << " Name=" << '"' << 1 << '"' << "/></MasterView></Include>";
    plik[1].v++;
    plik[1].c++;
    y += 100;
    plik[2].Y += y; */

       // fo <<"include..."; - for includes
    
    while(std::getline(fi2, str))
    {
        fo<<str;
    }
    
    for(int j = 1; j <= i; j++)
    fo << "\n<UseCase Id=" << '"' << plik[j].fileID << '"' << " Name=" << '"' << plik[j].filename << '"' << ">" << "\n</UseCase>";
  //  fo << "\n<UseCase Id=" << '"' << plik[2].fileID << '"' << " Name=" << '"' << plik[2].filename << '"' << ">" << "\n</UseCase>";
    
    fo << "</Models>\n<Diagrams>\n";
    
    while(std::getline(fi3, str))
       {
           fo<<str;
       }
    
    fo << "\n";
    for(int j = 1; j <= i; j++)
    {
    plik[j].c = 1;
    plik[j].v = 1;
    }
    
    for (auto const& t : IDmap) {
    z = t.first;
    y = plik[z].Y + 100;
    x = plik[z].X;
    for (int j = 0; j < t.second.size(); j++)
    {
        z2 = t.second[j];
        
    fo << "<Include Id=" << '"' << plik[z].fileID << "v" << plik[z].v << '"' << " From=" << '"' << plik[z].fileID << "s" << '"' << " MetaModelElement=" << '"' << plik[z].fileID << "c" << plik[z].c << '"' << " Model=" << '"' << plik[z].fileID << "c" << plik[z].c << '"' << " ZOrder=" << '"' << ZOrder << '"' << " To=" << '"' << plik[z2].fileID << "s" << '"' << " ";
    while(std::getline(fi5, str))
          {
              fo<<str;
          }
    ZOrder += 2;
    fi5.clear();
    fi5.seekg(0);
    fo << " X=" << '"' <<  55 + plik[z].X + (plik[z2].X - plik[z].X)/2 << '"' << " Y=" << '"' << 27 + plik[z].Y + (plik[z2].Y - plik[z].Y)/2 << '"' << "/></Include>";
        plik[z].v++;
        plik[z].c++;
        
    }
    }
    
     // fo <<"include..."; - for includes x2
    
    fo << "</Connectors><Shapes>";
    
    for(int j = 1; j <= i; j++)
    {
    fo << "\n<UseCase Id=" << '"' << plik[j].fileID << "s" << '"' << " MetaModelElement=" << '"' << plik[j].fileID << '"' << " Model=" << '"' << plik[j].fileID << '"' << " Name=" << '"' << plik[j].filename << '"' <<" X=" << '"' << plik[j].X << '"' << " Y=" << '"' << plik[j].Y << '"' <<" ZOrder=" << '"' << ZOrder << '"' << " ";
    while(std::getline(fi4, str))
          {
              fo<<str;
          }
    ZOrder += 2;
    fi4.clear();
    fi4.seekg(0);
    }
    
    
    
    fo << "</Shapes></UseCaseDiagram></Diagrams></Project>";
    
    fi.close();
    fi2.close();
    fi3.close();
    fi4.close();
    fi5.close();
    fo.close();
}
