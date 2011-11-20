#include <screens/vrScreenSelectMusic.h>
#include <system/vrSystem.h>
#include <core/vrGame.h>
#include <core/vrMusic.h>

#include <map>
using std::map;

VRScreenSelectMusic::VRScreenSelectMusic(string name) :
	VRScreen(name) {
}

VRScreenSelectMusic::~VRScreenSelectMusic() {
}

void VRScreenSelectMusic::open() {
	char filename[2048];
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	smgr->clear();
	strcpy(filename, VRSystem::getInstance()->getAppDir());
	strcat(filename, "media/musicSelection.irr");
	printf("Loading irr file from '%s'\n", filename);
	fflush(stdout);
	smgr->loadScene(filename);

	map<string, VRMusic*> musics;
	musics = VRGame::getInstance()->getMusics();
	selectedMusic = (musics.size() > 0) ? 0 : -1;	
}

void VRScreenSelectMusic::close() {

}

void VRScreenSelectMusic::render() {
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();	
	smgr->drawAll();
	char texto[1024];
	map<string, VRMusic*> musics;

	sprintf(texto, " Select a music");
	VRSystem::getInstance()->writeText(texto, 0, 0);

	musics = VRGame::getInstance()->getMusics();
	map<string, VRMusic*>::iterator it;
	int i=0;
	for (it = musics.begin(); it != musics.end(); ++it, i++) {
		int j = 20 + i*20;
		if (i == selectedMusic) {
			VRSystem::getInstance()->getDriver()->draw2DRectangle(core::rect<s32>(50,j,60,j+10),
			video::SColor(255,255,255,255), video::SColor(255,255,255,255),
			video::SColor(255,255,255,255), video::SColor(255,255,255,255));
		}
		string musicDescription = it->first;
		sprintf(texto, musicDescription.c_str());
		VRSystem::getInstance()->writeText(texto, 100, j);
	}
}

void VRScreenSelectMusic::OnInputEvent(int playerNum,
		int key, bool pressed, bool shiftState) {
	VRScreen::OnInputEvent(playerNum, key, pressed,
			shiftState);

	//Add new players, if needed
	if ( (key == VR_KEY_START)) {
		if (VRGame::getInstance()->getCredits()>0) {
			VRGame::getInstance()->addNewPlayer(playerNum);
			VRSystem::getInstance()->getScreenManager().setCurrentScreen("selectMusic");
			VRGame::getInstance()->setMusicSelectorPlayer(playerNum);
		}
	}
	//Player is the music selector 
	map<string, VRMusic*> musics;
	musics = VRGame::getInstance()->getMusics();
	if (playerNum==VRGame::getInstance()->getMusicSelectorPlayer()) {
		//Selects music
		if (!pressed) {
			if (key == VR_KEY_UP) {
				selectedMusic -= 1;
				if (selectedMusic<0)
					selectedMusic = musics.size()-1;
			} else if (key == VR_KEY_DOWN) {
				selectedMusic += 1;
				if (selectedMusic>(int)musics.size()-1)
					selectedMusic = (musics.size()==0) ? -1
							: 0;
			}
		}
		if (pressed) {
			// goes to the select difficult screen
			if (key == VR_KEY_START) {				
				//selects the music 
				map<string, VRMusic*>::iterator it;
				int i=0;
				for (it = musics.begin(); it != musics.end(); ++it, i++) {
					if (i == selectedMusic) 
						VRGame::getInstance()->selectMusic(it->first);
				}
				//change screen
				VRSystem::getInstance()->getScreenManager().setCurrentScreen("selectDifficult");
			}
		}
	}
}
