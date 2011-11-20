#include <core/vrGame.h>
#include <system/vrSystem.h>

#include <iostream>
#include <fstream>
using namespace std;

bool instanceFlagGame;
VRGame * _instanceGame;

VRGame * VRGame::getInstance() {
	if (!instanceFlagGame) {
		_instanceGame = new VRGame();
		instanceFlagGame = true;
	}
	return _instanceGame;
}

VRGame::VRGame() {
	credits = 0;
	musicSelectorPlayer = -1;	
	currentScenario = 0;
}

VRGame::~VRGame() {
	instanceFlagGame = false;
}

void VRGame::loadFromFile(string file) {
	string line;
	ifstream fd;
	fd.open(file.c_str(),
	//"C:\\pastas\\marcelo\\projetos\\Prog\\C\\VivaRock\\config\\config.cfg",
			ios::in);

	//Get Game Name
	getline(fd, line);
	this->title = line;
	//fd >> this->title;
	fd >> this->majorVersion;
	fd >> this->minorVersion;	
	
	printf("config file:  '%s' '%d' '%s' '%d' '%d'\n",
			file.c_str(), (fd.is_open()) ? 1 : 0,
			title.c_str(), majorVersion, minorVersion);
	fflush(stdout);

	//advance to next $, ignore rest of the header
	while (line[0] != '$') {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
	}
	//Load scenarios
	do {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
		if (line[0] != '$')
			scenarios.insert(
					scenarios.end(),
					new VRScenario(string(VRSystem::getInstance()->getAppDir()) + "config/scenarios/" + line + ".cen"));
	} while (line[0] != '$');
	chooseRandomScenario();	
	
	//Load musics
	do {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
		if ((!fd.eof()) && (line != ""))
			musics[line]
					= new VRMusic(line, string(VRSystem::getInstance()->getAppDir()) + "config/music/" + line + "/" + line + ".msc");
	} while (!fd.eof());

	fd.close();
}

