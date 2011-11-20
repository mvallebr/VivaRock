#include <core/vrMusicTrack.h>
#include <core/vrChord.h>
#include <system/vrSystem.h>
#include <iostream>
#include <fstream>
#include <list>
using std::list;
using namespace std;

VRMusicTrack::VRMusicTrack(string musicName, string line) {
	//track name
	string::size_type oldPos;
	string::size_type pos;
	oldPos = 0;
	pos = line.find(' ', oldPos);
	this->trackName = line.substr(oldPos, pos -oldPos);
	printf("Track name = '%s'\n", this->trackName.c_str());
	fflush(stdout);
	string temp;
	//sound
	oldPos = pos+1;
	pos = line.find(' ', oldPos);
	temp = line.substr(oldPos, pos-oldPos);
	string sfName = string(VRSystem::getInstance()->getAppDir()) + "media/" + temp;
	printf("Loading sound '%s'\n", sfName.c_str());
	fflush(stdout);
	VRSound *snd = new VRSound(sfName);
	this->sound = snd;
	//track easy
	oldPos = pos+1;
	pos = line.find(' ', oldPos);
	temp = line.substr(oldPos, pos-oldPos);
	sfName = string(VRSystem::getInstance()->getAppDir()) + "config/music/" + musicName
			+ "/" + temp;
	printf("Loading track easy '%s'\n", sfName.c_str());
	fflush(stdout);
	loadChordsFromFile(sfName, 0);	
	//track medium 
	oldPos = pos+1;
	pos = line.find(' ', oldPos);
	temp = line.substr(oldPos, pos-oldPos);
	sfName = string(VRSystem::getInstance()->getAppDir()) + "config/music/" + musicName
			+ "/" + temp;
	printf("Loading track medium '%s'\n", sfName.c_str());
	fflush(stdout);
	loadChordsFromFile(sfName, 1);	
	//track hard
	oldPos = pos+1;
	pos = line.find(' ', oldPos);
	temp = line.substr(oldPos, pos-oldPos);
	sfName = string(VRSystem::getInstance()->getAppDir()) + "config/music/" + musicName
			+ "/" + temp;	
	printf("Loading track hard '%s'\n", sfName.c_str());
	fflush(stdout);
	loadChordsFromFile(sfName, 2);	
	//instrument type
	oldPos = pos+1;
	pos = line.find('\n', oldPos);
	temp = line.substr(oldPos, pos-oldPos);
	VRSystem::getInstance()->stringTrim(temp);
	this->instrument = (temp == "BAIXO" ? BAIXO : (temp
			== "BATERIA" ? BATERIA : GUITARRA));
	printf("Instrument type (%d): '%s' \n",
			this->instrument, temp.c_str());
	fflush(stdout);
}

VRMusicTrack::~VRMusicTrack() {
}

void 
VRMusicTrack::loadChordsFromFile(string filename, int difficult) {
	printf("Loading track from file '%s'\n",
			filename.c_str());
	fflush(stdout);

	//load the file
	string line;
	ifstream fd;
	fd.open(filename.c_str(), ios::in);

	// Get pointsToWin	
	fd >> this->pointsToWin[difficult];	 
	printf("pointsToWin = %d\n", this->pointsToWin[difficult]);
	fflush(stdout);
	//check end of file
	if (fd.eof()) {
		fprintf(stderr, "Error: File is empty: '%s'\n", filename.c_str());
		fflush(stderr);
		exit(-1);
	}

	//advance to next $, ignore rest of the header
	getline(fd, line);
	while (line[0] != '$') {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
	}
	//Load chords, one per line
	list<VRChord *> chordsList;
	do {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
		if (line[0] != '$') {
			if (line.length()>0) {
				VRChord *newChord = new VRChord(line);
				chordsList.insert(chordsList.end(),
						newChord);
			}
		}
	} while (!fd.eof());
	//Sort by miliseconds
	VRChordFunctor f;
	chordsList.sort(f);
	//print sorted list
	list<VRChord *>::iterator it;
	for (it = chordsList.begin(); it != chordsList.end(); ++it) {
		VRChord *chord = *it;
		chords[difficult].insert(chords[difficult].end(), chord);
		//		printf("chords miliseconds = %ld\n",
		//					chord->getMiliSecondsFromBeginning());
	}

	fd.close();
}

