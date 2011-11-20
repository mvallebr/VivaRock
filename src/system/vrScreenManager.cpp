#include <system/vrScreenManager.h>

VRScreenManager::VRScreenManager() {
}
VRScreenManager::~VRScreenManager() {
}

void VRScreenManager::add(VRScreen* screen) {
	string name = screen->getName();
	screens[name] = screen;
	if (screens.size()<=1)
		setCurrentScreen(name);
}

VRScreen *VRScreenManager::getCurrentScreen() {
	return screens[currentScreen];
}

void VRScreenManager::setCurrentScreen(string screenName) {
	//Send close event to the old screen
	if (getCurrentScreen()!=NULL)
		getCurrentScreen()->close();
	//actually change the current screen
	currentScreen = screenName;
	//send open event for the openned screen
	if (getCurrentScreen()!=NULL)
		getCurrentScreen()->open();
}

void VRScreenManager::render() {
	if (getCurrentScreen()!=NULL)
		getCurrentScreen()->render();
}

void VRScreenManager::sendInputEvent(int playerNum, int key, bool pressed,
		bool shiftState) {
	if (getCurrentScreen()!=NULL)
		getCurrentScreen()->OnInputEvent(playerNum, key, pressed, shiftState);
}

