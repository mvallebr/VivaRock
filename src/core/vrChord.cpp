#include "vrChord.h"
 
VRChord::VRChord(string text) {
	printf("Parsing chord '%s'\n", text.c_str());
	fflush(stdout);
	//Parse chord	
	string::size_type oldPos;
	string::size_type pos;
	string temp;
	int tempi=0, milisec=0;

	//Find hours
	oldPos = 0;
	pos = text.find(':', oldPos);
	temp = text.substr(oldPos, pos - oldPos);
	tempi = atoi(temp.c_str());
	milisec = milisec* 60 + tempi;
//	printf("temp = '%s', tempi = '%d'\n", temp.c_str(),	tempi);
	fflush(stdout);

	//Find minutes
	oldPos = pos+1;
	pos = text.find(':', oldPos);
	if (pos!=string::npos) {
		temp = text.substr(oldPos, pos - oldPos);
		tempi = atoi(temp.c_str());
		milisec = milisec* 60 + tempi;
//		printf("temp = '%s', tempi = '%d'\n", temp.c_str(), tempi);
		fflush(stdout);
	} else {
		pos = oldPos-1;
	}

	//Find seconds
	oldPos = pos+1;
	pos = text.find(' ', oldPos);
	if (pos!=string::npos) {
		temp = text.substr(oldPos, pos - oldPos);
		tempi = atoi(temp.c_str());
		milisec = milisec* 60 + tempi;
//		printf("temp = '%s', tempi = '%d'\n", temp.c_str(),	tempi);
		fflush(stdout);
	} else {
		pos = oldPos-1;
	}
	//Find miliseconds
	oldPos = pos+1;
	pos = text.find(' ', oldPos);
	if (pos!=string::npos) {
		temp = text.substr(oldPos, pos - oldPos);
		tempi = atoi(temp.c_str());
		milisec = milisec* 1000 + tempi;
//		printf("temp = '%s', tempi = '%d'\n", temp.c_str(), tempi);
		fflush(stdout);
	}
	miliSecondsFromBeginning = milisec;

	//Find notes
	oldPos = pos+1;
	pos = text.length();
	if (pos!=string::npos) {
		temp = text.substr(oldPos, pos - oldPos);		
		for (unsigned int i=0; i < 5; i++) {
			notes[i]=false;
		}
		for (unsigned int i=0; i < temp.length(); i++) {			
			if (temp[i]=='A')
				notes[0] = true;
			if (temp[i]=='B')
				notes[1] = true;
			if (temp[i]=='C')
				notes[2] = true;
			if (temp[i]=='D')
				notes[3] = true;
			if (temp[i]=='E')
				notes[4] = true;
		}
	}
	//print summary
	printf(
			"miliSecondsFromBeginning = %ld, notes= (A:%s, B:%s, C:%s, D:%s, E:%s\n",
			miliSecondsFromBeginning, (notes[0] ? "true"
					: "false"), (notes[1] ? "true"
					: "false"), (notes[2] ? "true"
					: "false"), (notes[3] ? "true"
					: "false"), (notes[4] ? "true"
					: "false"));
}

VRChord::~VRChord() {
}
