#ifndef VRMUSIC_H_
#define VRMUSIC_H_

#include <string>
using std::string;
#include <vector>
using std::vector;

#include <system/vrSound.h>
#include <core/vrMusicTrack.h>

class VRMusic {
private:
	string musicName;
	unsigned long timeOffset;

	vector<VRSound *> sounds;
	vector<VRMusicTrack *> tracks;

	void loadFromFile(string name, string file);
public:
	VRMusic(string name, string file);
	virtual ~VRMusic();

	inline unsigned long getTimeOffset() {
		return timeOffset;
	}
	inline VRSound *getTrackSoundByTrackType(
			TrackType intrumentType) {
		VRSound *trackSound= NULL;
		for (unsigned int i=0; i< tracks.size(); i++) {
			VRMusicTrack *track = tracks.at(i);
			if (track->getInstrument() == intrumentType)
				trackSound = track->getSound();
		}
		return trackSound;
	}
	inline VRSound *getMusicSound(unsigned int i) {
		return sounds.at(i);
	}
	inline unsigned int getNumberOfSounds() {
		return sounds.size();
	}
	inline VRMusicTrack * getTrack(TrackType intrumentType) {
		VRMusicTrack *ptrack= NULL;
		for (unsigned int i=0; i< tracks.size(); i++) {
			VRMusicTrack *track = tracks.at(i);			
			if (track->getInstrument() == intrumentType)
				ptrack = track;
		}
		return ptrack;
	}
};

#endif /*VRMUSIC_H_*/
