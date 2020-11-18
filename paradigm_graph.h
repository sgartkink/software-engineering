#include <fstream>
#include <sstream>
#include <map>
#include <vector>

struct paradigmID {
	std::string filename;
	int fileID;
};
std::vector<paradigmID> filesID;
std::map<int, std::vector<int>> IDmap;
int findID(std::string x) {
	for (int i = 0; i < filesID.size(); i++) {
		if (filesID[i].filename == x)
			return filesID[i].fileID;
	}
}
void files_graph(std::string file_name, std::list<std::string> files_list, search::our_map map) {
	std::stringstream name, name2;
	std::string s, s2, name3, name4;
	int usecaseid = 1;
	for (auto it = files_list.begin(); it != files_list.end(); ++it) {
		name << *it;
		s = name.str();
		name3 = getname(s);
		filesID.push_back({name3,usecaseid});
		usecaseid++;
	}
	for (auto it = files_list.begin(); it != files_list.end(); ++it) {
		name << *it;
		s = name.str();
		name3 = getname(s);
		filesID.push_back({ name3,usecaseid });
		for (auto const& include : map[*it].includes) {
			int j = 0;
			name2 << include;
			s2 = name2.str();
			name4 = getname(s2);
			IDmap[usecaseid].push_back(findID(name4));
			j++;
		}
		usecaseid++;
	}
	for (auto const& x : IDmap) {
		std::cout << x.first << ":" << std::endl;
		for(int i = 0; i < x.second.size();i++)
			std::cout << x.second[i] << std::endl;
	}
}
