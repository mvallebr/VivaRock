#ifndef VRSCREENSELECTMUSIC_H_
#define VRSCREENSELECTMUSIC_H_

#include <system/vrScreen.h>
#include <core/vrPlayer.h>

#include <irrlicht.h>
using namespace irr;

class VRScreenSelectMusic : public VRScreen {
private:
	int selectedMusic;
public:
	VRScreenSelectMusic(string name);
	virtual ~VRScreenSelectMusic();
	virtual void open();
	virtual void close();
	virtual void render();
	virtual void OnInputEvent(int playerNum, int key, bool pressed,
			bool shiftState);
};

#endif /*VRSCREENSELECTMUSIC_H_*/
