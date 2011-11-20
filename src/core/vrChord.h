#ifndef VRCHORD_H_
#define VRCHORD_H_

#include <string>
using std::string;

class VRChord {
private:
	unsigned long miliSecondsFromBeginning;
	bool notes[5];
public:
	VRChord(string text);
	virtual ~VRChord();
	inline unsigned  long getMiliSecondsFromBeginning() {
		return miliSecondsFromBeginning;
	}
	inline bool getNote(int i) {
		return notes[i];
	}
};

struct VRChordFunctor {
	bool operator()(const VRChord *a, const VRChord *b) {	
		return (((VRChord *)a)->getMiliSecondsFromBeginning()
				< ((VRChord *)b)->getMiliSecondsFromBeginning());
	}
};

#endif /*VRCHORD_H_*/
