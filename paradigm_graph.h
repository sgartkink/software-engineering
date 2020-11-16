#include <fstream>
#include <sstream>
#include <vector>

struct paradigmID {
	std::string filename;
	int fileID;
};
std::vector<paradigmID> filesID;
std::map<paradigmID, std::string> IDmap;
void files_graph(std::string file_name, std::list<std::string> files_list, search::our_map map) {
	std::string x = file_name + ".csv";
	std::stringstream name;
	std::string s, name2;
	std::ofstream file(x);
	int usecaseid = 1, modelid = 3;
	std::string userid = "UC01";  //!!!
	file << "Diagram;ID;Name;Type;Description;Parent;Model;Delete ?\n";
	file << ";" << usecaseid << ";" << file_name << "; UseCaseDiagram;;;;No\n\n";
		++usecaseid;
	for (auto it = files_list.begin(); it != files_list.end(); ++it) {
		name << *it;
		s = name.str();
		name2 = getname(s);
		file << "Use Case;ID;Model ID;Name;Parent User ID;User ID;Stereotypes;Rank;Abstract;Leaf;Root;Business Model;Description;Transit From;Transit To;Parent ID;Parent Name;Delete ?\n";
		file << ";" << usecaseid << ";" << modelid << ";" << name2 << ";;"<< userid <<";<<UseCase>>;Unspecified;No;No;No;No;;;;;;No\n\n";
		filesID.push_back({name2,usecaseid});

		usecaseid++;
		modelid+=2;
	}

	for (int i = 0; i < filesID.size(); i++) {
		std::cout << filesID[i].filename << " "<< filesID[i].fileID << std::endl;
	}
	file << "Include;ID;Model ID;Name;Stereotypes;Including Case;Addition;Visibility;Description;Transit From;Transit To;Parent ID;Parent Name;Delete ?\n";

	file.close();
}
