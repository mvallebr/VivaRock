#include <system/vrGameLoop.h>
#include <system/vrSystem.h>
#include <core/vrGame.h>
#include <screens/vrScreenTest.h>
#include <screens/vrScreenTest3d.h>
#include <screens/vrScreenGame.h>
#include <screens/vrScreenSelectDifficult.h>
#include <screens/vrScreenSelectMusic.h>
#include <screens/vrScreenStartUp.h>

#include <irrlicht.h>
using namespace irr;

VRGameLoop::VRGameLoop() {
}

VRGameLoop::~VRGameLoop() {
}
void VRGameLoop::init() {
	//First, load the config files
	string configFile;
	configFile = VRSystem::getInstance()->getAppDir();
	configFile += "/config/config.cfg";
	VRGame::getInstance()->loadFromFile(configFile);
	
	//Next, create the screens
	VRSystem::getInstance()->getScreenManager().add(new VRScreenTest(string("test")));
	VRSystem::getInstance()->getScreenManager().add(new VRScreenTest3d(string("test3d")));
	VRSystem::getInstance()->getScreenManager().add(new VRScreenGame(string("game")));
	VRSystem::getInstance()->getScreenManager().add(new VRScreenSelectDifficult(string("selectDifficult")));
	VRSystem::getInstance()->getScreenManager().add(new VRScreenSelectMusic(string("selectMusic")));
	VRSystem::getInstance()->getScreenManager().add(new VRScreenStartUp(string("startUp")));
	VRSystem::getInstance()->getScreenManager().setCurrentScreen("game");
}

void VRGameLoop::destroy() {
}

void VRGameLoop::run() {		
	while (VRSystem::getInstance()->deviceRunning()) {
		VRSystem::getInstance()->beginDraw();
		VRSystem::getInstance()->getScreenManager().render();		
		VRSystem::getInstance()->endDraw();
		if (VRSystem::getInstance()->getScreenManager().getCurrentScreen()->shouldQuit())
			break;
	}
}

