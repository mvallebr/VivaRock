#include <system/vrSystem.h>
#include <iostream>
#include <stdio.h>

#include <SDL/SDL.h>

bool instanceFlag;
VRSystem * _instance;

VRSystem * VRSystem::getInstance() {
	if (!instanceFlag) {
		_instance = new VRSystem();
		instanceFlag = true;
	}
	return _instance;
}

void VRSystem::beginDraw() {
	driver->beginScene(true, true, irr::video::SColor(255,
			0, 0, 0));
	//smgr->drawAll();
	//guienv->drawAll();
}
void VRSystem::endDraw() {
	driver->endScene();
}
bool VRSystem::deviceRunning() {
	return device->run();
}

void VRSystem::destroy() {
	if (device)
		device->drop();

	//Close SDL
	SDL_Quit();
}
void VRSystem::init(int argc, char *argv[],
		int screen_width, int screen_height) {
	//init SDL for audio
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		fprintf(stderr, "problem initializing SDL: %s\n", SDL_GetError());
		exit(1);
	}	

	// start up the engine

	VREventReceiver *receiver1 = new VREventReceiver();
	//device = createDevice(video::EDT_SOFTWARE,	
	device = createDevice(video::EDT_OPENGL,
	//device = createDevice(video::EDT_DIRECT3D9 ,
	//device = createDevice(video::EDT_BURNINGSVIDEO,			
			core::dimension2d<s32>(screen_width, screen_height),
	32, false/*full screen*/, false, false, receiver1);

	//	device =
	//	       createDevice(video::EDT_OPENGL, core::dimension2d<s32>(640, 480), 16, false);

	if (device == NULL) {
		fprintf(stderr,"Error creating the device driver!\n");
		exit(-1);
	}

	driver = device->getVideoDriver();
	if (driver == NULL) {
		fprintf(stderr, "Error creating the video device driver!\n");
		exit(-1);
	}
	smgr = device->getSceneManager();
	if (smgr == NULL) {
		fprintf(stderr, "Error creating the scene manager!\n");
		exit(-1);
	}
	//Load font
	font = device->getGUIEnvironment()->getBuiltInFont();

	//Set caption
	device->setWindowCaption(L"Viva Rock!!");
	//Calculates app dir
	if (strncmp(argv[0], "/cygdrive/", strlen("/cygdrive/")-1)==0) {
		app_dir[0]=argv[0][strlen("/cygdrive/")];
		app_dir[1]=':';
		app_dir[2]='\0';
		strcat(app_dir, argv[0]+strlen("/cygdrive/")+1);
	} else {
		strcpy(app_dir, argv[0]);
	}
	int numSlashesToIgnore=1;
	for (int i=strlen(app_dir)-1; i>=0; i--) {
		if ((app_dir[i]=='/') || (app_dir[i]=='\\')) {
			app_dir[i+1]='\0';
			numSlashesToIgnore--;
			if (numSlashesToIgnore<0)
			break;
		}
	}
	//strcpy(app_dir,"/windows/pastas/marcelo/projetos/Prog/C/VivaRock/");
	printf("app dir = '%s'\n", app_dir);fflush(stdout);
}

void VRSystem::writeText(char *message, int x, int y) {
	wchar_t wcstring[1024];
	for (int i=0; i<1024; i++) {
		wcstring[i]=L'\0';
	}
	mbstowcs(wcstring, message, strlen(message));
	if (font) {
		font->draw(wcstring, core::rect<s32>(x,y,x+300,y+50), video::SColor(255,255,255,255));
	} else {
		printf("nogui - msg >>> '%s' \n", message);
	}
}

void VRSystem::stringTrim(string& str) {
	// Trim Both leading and trailing spaces
	// Find the first character position after excluding leading blank spaces
	size_t startpos = str.find_first_not_of(" \t");
	// Find the first character position from reverse af  
	size_t endpos = str.find_last_not_of(" t");
	// if all spaces or empty return an empty string   
	if ((string::npos == startpos ) || (string::npos
			== endpos)) {
		str = "";
	} else
		str = str.substr(startpos, endpos-startpos+1);

	/* 
	 // Code for  Trim Leading Spaces only 
	 size_t startpos = str.find_first_not_of(� \t�); // Find the first character position after excluding leading blank spaces 
	 if( string::npos != startpos ) 
	 str = str.substr( startpos ); 
	 */

	/* 
	 // Code for Trim trailing Spaces only 
	 size_t endpos = str.find_last_not_of(� \t�); // Find the first character position from reverse af 
	 if( string::npos != endpos ) 
	 str = str.substr( 0, endpos+1 ); 
	 */
}
