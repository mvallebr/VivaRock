#ifndef VRSCREENTEST_H_
#define VRSCREENTEST_H_

#include <system/vrScreen.h>
#include <system/sceneNode.h>
#include <core/vrPlayer.h>

#include <irrlicht.h>
using namespace irr;

class VRScreenTest : public VRScreen {
private:
	char texto[1024];
	SceneNode * myNode;
	u32 time;
	scene::ICameraSceneNode* camera , *camera2;
public:
	VRScreenTest(string name);
	virtual ~VRScreenTest();

	virtual void open();
	void close();
	virtual void render();
	virtual void OnInputEvent(int playerNum, int key, bool pressed,
			bool shiftState);

};

#endif /*VRSCREENTEST_H_*/
