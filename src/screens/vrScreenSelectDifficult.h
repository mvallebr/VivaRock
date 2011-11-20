#ifndef VRSCREENSELECTDIFFICULT_H_
#define VRSCREENSELECTDIFFICULT_H_

#include <system/vrScreen.h>
#include <core/vrPlayer.h>

#include <irrlicht.h>
using namespace irr;
using irr::video::ITexture;

class VRScreenSelectDifficult : public VRScreen {
private:
	int selectedDifficult;
	ITexture *imageEasy, *imageMedium, *imageHard;
public:
	VRScreenSelectDifficult(string name);
	virtual ~VRScreenSelectDifficult();

	virtual void open();
	virtual void close();
	virtual void render();
	virtual void OnInputEvent(int playerNum, int key, bool pressed,
			bool shiftState);
};

#endif /*VRSCREENSELECTDIFFICULT_H_*/
