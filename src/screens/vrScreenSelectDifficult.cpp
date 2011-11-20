#include <screens/vrScreenSelectDifficult.h>
#include <system/vrSystem.h>
#include <core/vrGame.h>

VRScreenSelectDifficult::VRScreenSelectDifficult(string name) :
	VRScreen(name) {
}

VRScreenSelectDifficult::~VRScreenSelectDifficult() {
}

void VRScreenSelectDifficult::open() {
	char filename[2048];
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	smgr->clear();
	strcpy(filename, VRSystem::getInstance()->getAppDir());
	strcat(filename, "media/difficultSelection.irr");
	printf("Loading irr file from '%s'\n", filename);
	fflush(stdout);
	smgr->loadScene(filename);

	string fname;
	fname = VRSystem::getInstance()->getAppDir();
	fname += "media/dif_facil.png";
	printf("Loading png file from '%s'\n", fname.c_str());
	fflush(stdout);
	imageEasy = VRSystem::getInstance()->getDriver()->getTexture(fname.c_str());
	if (!(imageEasy)) {
		fprintf(stderr, "Could't load image!!!\n");
		fflush(stderr);
		quitApp();
	}
	fname = VRSystem::getInstance()->getAppDir();
	fname += "media/dif_medio.png";
	imageMedium = VRSystem::getInstance()->getDriver()->getTexture(fname.c_str());
	if (!(imageMedium)) {
		fprintf(stderr, "Could't load image!!!\n");
		fflush(stderr);
		quitApp();
	}
	fname = VRSystem::getInstance()->getAppDir();
	fname += "media/dif_dificil.png";
	imageHard = VRSystem::getInstance()->getDriver()->getTexture(fname.c_str());
	if (!(imageHard)) {
		fprintf(stderr, "Could't load image!!!\n");
		fflush(stderr);
		quitApp();
	}

	selectedDifficult = 1;
}

void VRScreenSelectDifficult::close() {

}

void VRScreenSelectDifficult::render() {
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	smgr->drawAll();

	VRSystem::getInstance()->getDriver()->draw2DImage(imageEasy, core::position2d<s32>(100, 100),
	core::rect<s32>(core::position2d<s32>(0, 0), imageEasy->getSize()),
	0, video::SColor(255, 255, 255, 255), true
	);
	VRSystem::getInstance()->getDriver()->draw2DImage(imageMedium,
	core::position2d<s32>(100, 200),
	core::rect<s32>(core::position2d<s32>(0, 0), imageEasy->getSize()),
	0, video::SColor(255, 255, 255, 255), true
	);
	VRSystem::getInstance()->getDriver()->draw2DImage(imageHard,
	core::position2d<s32>(100, 300),
	core::rect<s32>(core::position2d<s32>(0, 0), imageEasy->getSize()),
	0, video::SColor(255, 255, 255, 255), true
	);

	if (selectedDifficult>-1) {
		int y=100+selectedDifficult*100;
		VRSystem::getInstance()->getDriver()->draw2DRectangle(core::rect<s32>(50,y,60,y+10),
		video::SColor(255,255,255,255), video::SColor(255,255,255,255),
		video::SColor(255,255,255,255), video::SColor(255,255,255,255));
	}
}

void VRScreenSelectDifficult::OnInputEvent(int playerNum,
		int key, bool pressed, bool shiftState) {
	VRScreen::OnInputEvent(playerNum, key, pressed,
			shiftState);
	if (playerNum==VRGame::getInstance()->getMusicSelectorPlayer()) {
		//Selects music
		if (!pressed) {
			if (key == VR_KEY_UP) {
				selectedDifficult -= 1;
				if (selectedDifficult<0)
					selectedDifficult = 2;
			} else if (key == VR_KEY_DOWN) {
				selectedDifficult += 1;
				if (selectedDifficult>2)
					selectedDifficult = 0;
			}
		}
		if (pressed) {
			// goes to the select difficult screen
			if (key == VR_KEY_START) {
				VRGame::getInstance()->selectdifficult(selectedDifficult);
				VRSystem::getInstance()->getScreenManager().setCurrentScreen("game");
			}
		}
	}
}
