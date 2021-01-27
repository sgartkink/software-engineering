#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>



void cs()
{
    std::string sname = "lizcnn.sh";
    std::ofstream script(sname);
    script << "#/bin/bash\n";
    script << "lizard ../software-engineering > ../lc.txt";
    script.close();
    sname = "./" + sname;
    system("chmod +x lizcnn.sh");
    system((sname).c_str());
}

void lc2()
{
    std::ifstream lc;
    std::ofstream lc2;
    char ch;
    
    lc.open("../lc.txt");
    lc2.open("../lc2.txt");
    int i = 0, j = 0, k =0, a = 0, b = 0, c = 0, d = 0;
    std::string str, str2;
    while(lc >> std::noskipws >> ch)
    {
        ++i;
        if(i < 148)
        {
            a = 1;
            continue;
        }
        if( b == -2 && ch >= 46 && d == 1)
        {
            lc2 << ch;
            d = 0;
            continue;
        }
        else if(d == 1)
        {
            d = 0;
            continue;
        }
       if(ch >= 46 || ch == 10)
       {
           if (c == 2 && ch != 10)
           {
               str += ch;
               continue;
           } else if(ch == 10)
           {
               c = 0;
               str += ch;
               lc2 << str;
               str = "";
               b = 0;
               continue;
           }
           if(ch == 100)
               j = 1;
           else if(ch == 46)
               k = 1;
           else{ k = 0; j = 0;}
           if(j == 1 && k == 1)
               break;
           if(a == 1)
           {
               a = 0;
               ++b;
           }
           if(b == 2)
           {
               ++c;
               b = -2;
               d = 1;
               lc2 << ch;
               continue;
           }
       }
       else a = 1;
    }

    lc.close();
    lc2.close();
}

void lc3()
{
    std::ifstream lc2;
    std::ofstream lc3;
    lc2.open("../lc2.txt");
    lc3.open("../lc3.txt");
    std::string str, str2;
    int a = 0, b = 0, c = 0;
    char x = 92;
    while(std::getline(lc2,str))
    {
        if(a == 0)
        {
            a = 1;
            str2 = getname(str);
            if(str[1] >= 48 && str[1] <= 57)
            {
                b=((str[0]-48) * 10) + str[1] -48;
            }else if(str[0] >= 48 && str[0] <= 57){
                b= str[0] - 48;
            }
            c += b;
            continue;
        }

        
        
        if(getname(str) == str2)
        {
            if(str[1] >= 48 && str[1] <= 57)
            {
                b=((str[0]-48) * 10) + str[1] -48;
            }else if(str[0] >= 48 && str[0] <=57){
                b= str[0] - 48;
            }
            c+=b;
            b = 0;
            continue;
        }
        else
        {
            
            lc3 << c << x << str2 << "\n";
            c = 0;
            b = 0;
            if(str[1] >= 48 && str[1] <= 57)
            {
                b=((str[0]-48) * 10) + str[1] -48;
            }else if(str[0] >= 48 && str[0] <=57){
                b= str[0] - 48;
            }
            c+=b;
            str2 = getname(str);
        }
    }
    lc2.close();
    lc3.close();
}

//std::list<std::string> files_list, search::our_map map
void making_cnn_graph(std::string graph_name, std::list<std::string> files_list, search::our_map map)
{
    std::string x = graph_name + ".gv";
        std::ofstream file(x);
        std::stringstream name, name2;
        std::string s, s2;

    int a = 0, b = 0;

  //  int a = 0, b =0;
        file << "digraph cnn_graph\n{\n";
        for (auto it = files_list.begin(); it != files_list.end(); ++it) {
            for (auto const& include : map[*it].includes) {
                name << *it;
                s = name.str();
                name2 << include;
                s2 = name2.str();
                s = getname(s);
                s2 = getname(s2);
                std::string str;
                        std::ifstream lc4;
                    lc4.open("../lc3.txt");
                while(std::getline(lc4, str))
                {
                    if(s == getname(str) && a == 0)
                    {
                        a = 1;
                        s += 32;
                        if(str[1] >= 48 && str[1] <= 57)
                        {
                            s += str[0];
                            s += str[1];
                        }
                        else s+= str[0];
                    }
                    if(s2 == getname(str) && b == 0)
                    {
                        b = 1;
                        s2 += 32;
                        if(str[1] >= 48 && str[1] <= 57)
                        {
                            s2 += str[0];
                            s2 += str[1];
                        }
                        else s2+= str[0];
                    }

                }
                a = 0;
                b = 0;
                lc4.clear();
                lc4.seekg(0);
                lc4.close();
                if(s != "graph_drawing.h 17")
                file << '"' << s << '"' << "->" << '"' << s2 << '"' << "[label = 1];" << "\n";
            }
        }
        file << "}";
        file.close();
        bash_files(graph_name);
    
}


void check_cnn(std::string graph_name, std::list<std::string> files_list, search::our_map map)
{
    cs();
    lc2();
    lc3();
    making_cnn_graph(graph_name,files_list, map);


}

