#ifndef VRSOUND_H_
#define VRSOUND_H_

#include <string>
using std::string;

#include "SDL/SDL.h"

class VRSound {
private:		
	int cIndex;
	bool play;
public:	
	VRSound(string file);
	virtual ~VRSound();
	void start();
	void pause();
	void stop();
	void setVolume(Uint8 volume);
	Uint8 getMaxVolume();
	

};

extern "C" {
void mixSetVolume(int index, Uint8 volume);
void mixSetPlay(int index, bool play);
void mixaudio(void *unused, Uint8 *stream, int len);
int OpenSound(const char *file);
void initSDLAudio();
void closeSDLAudio();
}

#endif /*VRSOUND_H_*/
