#include <fstream>
#include <sstream>
#include <map>
#include <vector>

std::map<std::string, int> filesID;
std::map<int, std::vector<int>> IDmap;

void files_graph(std::string file_name, std::list<std::string> files_list, search::our_map map) {
	std::stringstream name, name2;
	std::string s, s2, name3, name4;
	int usecaseid = 1;
	for (auto it = files_list.begin(); it != files_list.end(); ++it) {
		name << *it;
		s = name.str();
		name3 = getname(s);
		filesID[name3] = usecaseid;
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
}