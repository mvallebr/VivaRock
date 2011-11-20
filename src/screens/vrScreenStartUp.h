#ifndef VRSCREENSTARTUP_H_
#define VRSCREENSTARTUP_H_

#include <system/vrScreen.h>
#include <core/vrPlayer.h>

#define TEMPO_SEGUNDOS_INTRO_AVI   		10
#define TEMPO_SEGUNDOS_TEXTO_PISCANTE	15
#define TEMPO_SEGUNDOS_DEMO_AVI			10

enum ETAPAS { ETAPA_INTRO_AVI, ETAPA_TEXTO_PISCANTE, ETAPA_DEMO_AVI };

class VRScreenStartUp : public VRScreen {
private:
	u32 lastTime;
	char texto[1024];		 
	int etapa;
public:
	VRScreenStartUp(string name);
	virtual ~VRScreenStartUp();
	virtual void open();
	virtual void close();
	virtual void render();
	virtual void OnInputEvent(int playerNum, int key, bool pressed,
			bool shiftState);
};

#endif /*VRSCREENSTARTUP_H_*/
