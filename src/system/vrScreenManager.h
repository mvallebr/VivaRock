#ifndef VRSCREENMANAGER_H_
#define VRSCREENMANAGER_H_

#include <system/vrScreen.h>
#include <core/vrPlayer.h>

#include <string>
using std::string;

#include <map>
using std::map;

#include <irrlicht.h>
using namespace irr;

class VRScreenManager {
private:
	string currentScreen;	
	map<string, VRScreen *>  screens;	
public:
	VRScreenManager();
	~VRScreenManager();

	void add(VRScreen * screen);
	VRScreen *getCurrentScreen();
	void setCurrentScreen(string screenName);
	void render();
	void sendInputEvent(int playerNum, int key, bool pressed, bool shiftState);
};

#endif /*VRSCREENMANAGER_H_*/
