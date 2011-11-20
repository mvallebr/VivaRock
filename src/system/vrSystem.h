#ifndef __VR_SYSTEM_H__
#define  __VR_SYSTEM_H__

#include <iostream>
#include <irrlicht.h>
using namespace irr;

//Screen resolution
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#include <system/vrEventReceiver.h>
#include <system/vrScreenManager.h>

extern bool instanceFlag;
class VRSystem {
private:
	//	static bool instanceFlag;
	//	static VRSystem * _instance;	
	IrrlichtDevice *device;
	video::IVideoDriver* driver;
	scene::ISceneManager* smgr;
	gui::IGUIFont* font;
	char app_dir[1024];
	VREventReceiver eventReceiver;
	VRScreenManager screenManager;
	VRSystem() {
	}
public:
	~VRSystem() {
		instanceFlag = false;
	}
	void beginDraw();
	void endDraw();
	bool deviceRunning();

	void writeText(char *message, int x, int y);
	void init(int argc, char *argv[], int screen_width,
			int screen_height);
	void destroy();

	static VRSystem* getInstance();

	inline IrrlichtDevice * getDevice() {
		return device;
	}
	inline video::IVideoDriver* getDriver() {
		return driver;
	}
	inline scene::ISceneManager* getSceneManager() {
		return smgr;
	}
	inline VRScreenManager& getScreenManager() {
		return screenManager;
	}
	inline char* getAppDir() {
		return app_dir;
	}
	void stringTrim( string& str); 

};

#endif // __VR_SYSTEM_H__
