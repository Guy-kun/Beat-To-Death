#include "Simfile.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

Simfile::Simfile(String pathToFile){
	vector<string> lines = FileReader::ReadFile(pathToFile.getCString(), 'r');
	for (string line : lines){
		if (line.length() >= 2 && strcmp(line.substr(0, 2).c_str(), "\r") != 0){
			if (line.length() > 7 && strcmp(line.substr(0, 7).c_str(), "#TITLE:") == 0){
				string param = line.substr(7);
				param.erase(param.find_last_not_of(";")-1);
				title = String(param.c_str());
			}
			else if (line.length() > 8 && strcmp(line.substr(0, 8).c_str(), "#ARTIST:") == 0){
				string param = line.substr(8);
				param.erase(param.find_last_not_of(";") - 1);
				artist = String(param.c_str());
			}
			else if (line.length() > 7 && strcmp(line.substr(0, 7).c_str(), "#MUSIC:") == 0){
				string param = line.substr(7);
				param.erase(param.find_last_not_of(";") - 1);
				musicFilename = String(param.c_str());
			}
			else if (line.length() > 8 && strcmp(line.substr(0, 8).c_str(), "#OFFSET:") == 0){
				string param = line.substr(8);
				param.erase(param.find_last_not_of(";") - 1);
				offset = atof(param.c_str());
			}
			else if (line.length() > 6 && strcmp(line.substr(0, 6).c_str(), "#BPMS:") == 0){
				string param = line.substr(6);
				param.erase(param.find_last_not_of(";") - 1);
				for (string s : split(param, ','))
				{
					std::vector<string> vals = split(s, '=');
					string beat = vals[0];
					string bpm = vals[1];
					BPMs.push_back(std::pair<long,float>(atol(beat.c_str()), atof(bpm.c_str())));
				}
			}
		}
	}
}

Simfile::~Simfile(){

}