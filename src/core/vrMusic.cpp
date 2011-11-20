#include <core/vrMusic.h>
#include <system/vrSystem.h>
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
using std::string;

VRMusic::VRMusic(string name, string file) {
	this->musicName = name;
	loadFromFile(name, file);
}

VRMusic::~VRMusic() {
}

void VRMusic::loadFromFile(string name, string file) {
	printf("Loading music from file '%s'\n", file.c_str());
	fflush(stdout);

	this->musicName = name;
	
	//load the file
	string line;
	ifstream fd;
	fd.open(file.c_str(), ios::in);

	// Get time offset in miliSeconds	
	fd >> this->timeOffset;
	printf("time offset = %ld\n", this->timeOffset);
	fflush(stdout);
	//check end of file
	if (fd.eof()) {
		fprintf(stderr, "Error: File is empty: '%s'\n", file.c_str());
		fflush(stderr);
		exit(-1);
	}

	//advance to next $, ignore rest of the header
	getline(fd, line);
	while (line[0] != '$') {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
	}
	//Load sounds
	do {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
		if (line[0] != '$') {
			string sfName = string(VRSystem::getInstance()->getAppDir()) + "media/" + line;
			printf("Loading sound '%s'\n", sfName.c_str());
			fflush(stdout);
			VRSound *snd = new VRSound(sfName);
			sounds.insert(sounds.end(), snd); 
		}
	} while (line[0] != '$');

	//Load tracks
	do {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
		if (line[0] != '$') {
			VRMusicTrack *track = new VRMusicTrack(this->musicName, line);
			this->tracks.insert(this->tracks.end(), track);
		}
	} while (!fd.eof());

	fd.close();
}
