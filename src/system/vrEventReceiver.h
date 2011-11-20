#ifndef __VR_EVENT_RECEIVER_H__
#define  __VR_EVENT_RECEIVER_H__

#include <iostream>

#include <irrlicht.h>
using namespace irr;

#include <system/vrInput.h>

class VREventReceiver : public IEventReceiver {
private:
	char key[1024];
	int key_shifts;
	int key_pressed;
public:
	VREventReceiver() :
		IEventReceiver() {
		for (int i=0; i<1024; i++)
			key[i]='\0';
		key_shifts=0;
		key_pressed=0;
	}
	~VREventReceiver() {
	}

	virtual bool OnEvent(const SEvent& event);
	virtual int detectPlayerKey(int key);
	virtual int convertPlayerKey(int key);
};

#endif // __VR_EVENT_RECEIVER_H__
