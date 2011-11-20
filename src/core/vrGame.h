#ifndef VRGAME_H_
#define VRGAME_H_

#include <string>
using std::string;

#include <map>
using std::map;
#include <vector>
using std::vector;

#include <core/vrScenario.h>
#include <core/vrMusic.h>
#include <core/vrPlayer.h>

#define MAX_NUMBER_OF_PLAYERS 3

class VRGame {
private:
	int credits;
	string title;
	int minorVersion, majorVersion;
	vector<VRScenario *> scenarios;
	map <string, VRMusic*> musics;
	map <int, VRPlayer*> players;
	int musicSelectorPlayer;
	string currentMusic;
	int currentDifficult;
	int currentScenario;
public:
	VRGame();
	virtual ~VRGame();

	void loadFromFile(string file);
	static VRGame* getInstance();

	inline int getCurrentDifficult() {
		return currentDifficult;
	}
	inline void addCredits(int addedCredits) {
		this->credits += addedCredits;
	}
	inline void removeCredits(int remCredits) {
		this->credits -= remCredits;
	}
	inline void setCredits(int credits) {
		this->credits = credits;
	}
	inline int getCredits() {
		return this->credits;
	}
	inline map<string, VRMusic*> getMusics() {
		return musics;
	}
	inline VRMusic* getMusic(string name) {
		return musics[name];
	}
	inline VRMusic* getSelectedMusic() {
		return musics[currentMusic];
	}
	inline void selectMusic(string name) {
		if (musics[name]!=NULL)
			currentMusic = name;
	}
	inline void selectdifficult(int diff) {
		this->currentDifficult = diff;
	}
	inline VRPlayer* getPlayer(int playerNum) {
		return players[playerNum];
	}
	inline void setPlayer(int playerNum, VRPlayer *player) {
		players[playerNum] = player;
	}
	inline int getMusicSelectorPlayer() {
		return musicSelectorPlayer;
	}
	inline void setMusicSelectorPlayer(int msp) {
		musicSelectorPlayer = msp;
	}
	inline int getNumberOfPlayers() {
		return players.size();
	}
	inline void addNewPlayer(int playerNum) {
		if (getPlayer(playerNum)==NULL) {
			setPlayer(playerNum, new VRPlayer());
			removeCredits(1);
		}
	}
	inline void chooseRandomScenario() {
		//check number of scenarios
		if (scenarios.size()==0) {
			fprintf(stderr, "Error: Number of scenarios is zero!! Add at least one scenario\n");
			fflush(stderr);
			exit(-1);
		}
		currentScenario = rand() % scenarios.size();
	}
	inline VRScenario * getCurrentScenario() {
		return scenarios.at(currentScenario);
	}
};

#endif /*VRGAME_H_*/
