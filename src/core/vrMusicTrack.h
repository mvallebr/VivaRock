#ifndef VRMUSICTRACK_H_
#define VRMUSICTRACK_H_

#include <system/vrSound.h>
#include <core/vrChord.h>
#include <vector>
using std::vector;
#include <string>
using std::string;

typedef enum _TrackType {
	GUITARRA, BATERIA, BAIXO
} TrackType;


class VRMusicTrack
{
private:
	VRSound *sound;
	//One for easy, one for medium, one for hard
	unsigned int pointsToWin[3];
	vector<VRChord *> chords[3];
	string trackName;
	TrackType instrument;
	VRSound * trackSound;
	
public:
	VRMusicTrack(string musicName, string line);
	virtual ~VRMusicTrack();
	
	void loadChordsFromFile(string filename, int difficult);
	
	inline VRSound *getSound(){
		return sound;
	}
	inline TrackType getInstrument() {
		return instrument;
	}
	inline unsigned int getPointsToWin(int difficult) {
		return pointsToWin[difficult];
	}
	inline unsigned int getNumberOfChords(int difficult) {
		return chords[difficult].size();
	}
	inline VRChord * getChord(int difficult, unsigned int i) {
		return chords[difficult].at(i);
	}
};

#endif /*VRMUSICTRACK_H_*/
