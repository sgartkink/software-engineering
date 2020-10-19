
#include<iostream>
#include<fstream>
#include "list_files.h"

using namespace std;



int plik(string nazwa, string nazwa2){

    
    ifstream plik;
    plik.open(nazwa);
    
       if(plik.fail())
       {
           cout << "Błąd przy otwieraniu pliku\n";
           exit(1);
       }
    
    string szukamy = "#include";
    bool znalezione = 0;
    
    while(!plik.eof()){
        
        string linijka = "";
        getline(plik, linijka);
        for(int i=0;i<szukamy.size();i++)
        {
            if(linijka[i]==szukamy[i])
                znalezione = 1;
            else
            {
                znalezione =0;
                break;
            }
        }
        if(znalezione)
        {
        
            size_t gdzie = linijka.find(szukamy);
            if(linijka.find("#include") != string::npos){
                gdzie += szukamy.size();
                if( nazwa2 == linijka.substr(gdzie)){
                     plik.close();
                    return 1;
                }
               
            }
            
        }
        
        if(plik.eof()&&(!znalezione))
        {
            cout << "Nie znaleziono nazwy pliku\n";
        }

       
            
        }
        
        
    
       plik.close();
    return 0;
    
}
