#ifndef VRSCREEN_H_
#define VRSCREEN_H_

#include <string>
using std::string;

#include <irrlicht.h>
using namespace irr;

#include <core/vrPlayer.h>

class VRScreen  {
private:
	//int i;
	string name;
	bool   quit;
public:
	VRScreen(string name) { 
		this->name = name;
		quit = false;
	}
	virtual ~VRScreen() {}
	
	virtual void open()=0;
	virtual void close()=0;
	virtual void render()=0;
	virtual void OnInputEvent(int playerNum, int key, bool pressed, bool shiftState);
	
	
	inline bool   shouldQuit(){ return quit; }
	inline void   quitApp() { quit = true; }
	inline string getName() { return name; }
};

#endif /*VRSCREEN_H_*/
