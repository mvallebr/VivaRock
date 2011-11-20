#include <system/vrScreen.h>
#include <core/vrGame.h>
#include <system/vrInput.h>

void VRScreen::OnInputEvent(int playerNum, int key, bool pressed, bool shiftState) {
	if ((key == VR_KEY_CREDIT) && !pressed) {
		VRGame::getInstance()->addCredits(1);
	} else if ( (key == VR_KEY_ESC)) {
		quitApp();
	}
}

