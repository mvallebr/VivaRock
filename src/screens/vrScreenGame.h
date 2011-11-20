#ifndef VRSCREENGAME_H_
#define VRSCREENGAME_H_

#include <system/vrScreen.h>
#include <core/vrPlayer.h>
#include <system/vrSound.h>
#include <screens/vrRenderNode.h>
#include <core/vrGame.h>

#include <vector>
using std::vector;

#include <irrlicht.h>
using namespace irr;
using irr::video::ITexture;
using core::vector3df;
using irr::video::S3DVertex;

class VRScreenGame : public VRScreen {
private:
	VRSound *playerSound[MAX_NUMBER_OF_PLAYERS];
	vector<VRSound *> sounds;
	bool soundsStarted;
	unsigned long gameStartMilisec;
	ITexture *imgGuitarra;
	ITexture *imgNotas[5];

	scene::ICameraSceneNode* camera;
	scene::ISceneManager* smgrNotes, *smgrGuitars;
	VRRenderNode *guitarP1, *guitarP2, *guitarP3;
	vector <VRRenderNode *> notesP[3];

	unsigned long elapsedMiliSeconds;
	unsigned int points;
	unsigned long lastMiliSec;
	unsigned long lastAccMiliSec;
	int lastChord[MAX_NUMBER_OF_PLAYERS];
public:
	VRScreenGame(string name);
	virtual ~VRScreenGame();

	void updateNotesPositions(int playerNum, 
			unsigned long elapsedMiliSecondsFromLast);
	void startSounds();

	//	inline int getGuitarHeight() {
	//		return imgGuitarra->getSize().Height;
	//	}
	inline vector3df getNotesOrigin(int playerNum) {
		int offSet=0;
		if (playerNum==0) offSet = -VRGame::getInstance()->getCurrentScenario()->getGuitarra().leftOffset;
		else if (playerNum==2) offSet = VRGame::getInstance()->getCurrentScenario()->getGuitarra().leftOffset;
		
		vector3df center = vector3df(0, 50, 0);
		vector3df origin = center + vector3df(offSet
				- (imgGuitarra->getSize().Width/2), (imgGuitarra->getSize().Height/2), 0);
		return origin;
	}
	inline TrackType getPlayerTrack(int playerNum) {
		TrackType instrument=GUITARRA;
		VRPlayer *player = VRGame::getInstance()->getPlayer(playerNum);
		if (player!=NULL) {
			switch (playerNum) {
			case 0:
				instrument=GUITARRA;
				break;
			case 1:
				instrument = BATERIA;
				break;
			case 2:
				instrument = BAIXO;
				break;			
			default:
				instrument=GUITARRA;
				break;
			}
		}
		return instrument;
	}
	virtual void open();
	virtual void close();
	virtual void render();
	virtual void OnInputEvent(int playerNum, int key,
			bool pressed, bool shiftState);

};

#endif /*VRSCREENGAME_H_*/
