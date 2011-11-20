#include <core/vrScenario.h>
#include <system/vrSystem.h>

#include <iostream>
#include <fstream>
using namespace std;

VRScenario::VRScenario(string file) {
	printf("Loading scenario from file '%s'\n",
			file.c_str());
	string line;
	ifstream fd;
	fd.open(file.c_str(),
	//"C:\\pastas\\marcelo\\projetos\\Prog\\C\\VivaRock\\config\\config.cfg",
			ios::in);

	//check end of file
	if (fd.eof()) {
		fprintf(stderr, "Error: File is empty: '%s'\n", file.c_str());
		fflush(stderr);
		exit(-1);
	}

	//Get Scenario Description
	getline(fd, line);
	this->description = line;
	//Get Scenario irr file
	getline(fd, line);
	this->irrFile = line;

	printf("Loading scenario: \"%s\" irrFile: \"%s\" \n",
			this->description.c_str(),
			this->irrFile.c_str());
	fflush(stdout);

	//advance to next $, ignore rest of the header
	getline(fd, line);
	while ((line[0] != '$') && (!fd.eof())) {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
	}
	//check end of file
	if (fd.eof()) {
		fprintf(stderr, "Error: File is incomplete: '%s'\n", file.c_str());
		fflush(stderr);
		exit(-1);
	}
	// ------- Load guitar and notes images
	int pos, oldPos;
	string temp;
	//get instrument descriptor
	printf("a\n");
	fflush(stdout);
	getline(fd, line);
	printf("%s a\n", line.c_str());
	VRSystem::getInstance()->stringTrim(line);
	printf("a\n");
	fflush(stdout);
	this->instrument = (line == "BAIXO" ? BAIXO : (line
			== "BATERIA" ? BATERIA : GUITARRA));

	printf("a\n");
	fflush(stdout);
	//Load guitar image
	getline(fd, line);
	VRSystem::getInstance()->stringTrim(line);
	oldPos = 0;
	pos = line.find(' ', oldPos);
//	printf("pos1=%d %s\n", pos, line.substr(oldPos, pos).c_str());
	this->guitarra.imageFilename = line.substr(oldPos, pos);
	//load left offset	
	oldPos = pos+1;
	pos = line.find(' ', oldPos);	
	temp = line.substr(oldPos, pos);
//	printf("pos2=%d %s\n", pos, temp.c_str());
	this->guitarra.leftOffset = atoi(temp.c_str());
	//load notes colision offset
	temp = line.substr(pos+1, line.length());
	VRSystem::getInstance()->stringTrim(temp);
	this->offset_colisao_notas = atoi(temp.c_str());	
	printf(
			"Guitar image filename = '%s', instrument = '%d', offset = '%d', NOTES COLISION OFFSET = '%d'\n",
			this->guitarra.imageFilename.c_str(),
			this->instrument, this->guitarra.leftOffset, this->offset_colisao_notas);
	fflush(stdout);

	//Load notes
	for (int i=0; i<5; i++) {
		getline(fd, line);
		VRSystem::getInstance()->stringTrim(line);
		oldPos = 0;
		pos = line.find(' ', oldPos);
		this->notas[i].imageFilename = line.substr(0, pos);
		temp = line.substr(pos+1, line.length());
		VRSystem::getInstance()->stringTrim(temp);
		this->notas[i].leftOffset = atoi(temp.c_str());
		printf(
				"notes[%d] image filename = '%s', offset = '%d'\n",
				i, this->notas[i].imageFilename.c_str(),
				this->notas[i].leftOffset);
		fflush(stdout);
	}

	//  ---------- Load error offsets
	getline(fd, line);
	VRSystem::getInstance()->stringTrim(line);
	//First offset
	oldPos = 0;
	pos = line.find(' ', oldPos);	
	temp = line.substr(oldPos, pos);
	VRSystem::getInstance()->stringTrim(temp);
	this->offset_topo_aperto_botao = atoi(temp.c_str());
	//erro1_offset_topo_aperto_botao
	oldPos = pos+1;
	pos = line.find(' ', oldPos);	
	temp = line.substr(oldPos, pos);
	VRSystem::getInstance()->stringTrim(temp);
	this->erro1_offset_topo_aperto_botao = atoi(temp.c_str());
	//erro2_offset_topo_aperto_botao
	oldPos = pos+1;
	pos = line.length();	
	temp = line.substr(oldPos, pos);
	VRSystem::getInstance()->stringTrim(temp);
	this->erro2_offset_topo_aperto_botao = atoi(temp.c_str());

	printf(
			"offset_topo_aperto_botao=%d erro1_offset_topo_aperto_botao=%d erro2_offset_topo_aperto_botao=%d\n",
			this->offset_topo_aperto_botao,
			this->erro1_offset_topo_aperto_botao, this->erro2_offset_topo_aperto_botao);
	fflush(stdout);
	
	fd.close();
}

VRScenario::~VRScenario() {
}
