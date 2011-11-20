#include <screens/vrScreenStartUp.h>
#include <system/vrSystem.h>
#include <core/vrGame.h>

VRScreenStartUp::VRScreenStartUp(string name) :
	VRScreen(name) {
}

VRScreenStartUp::~VRScreenStartUp() {
}

void VRScreenStartUp::open() {
	lastTime = VRSystem::getInstance()->getDevice()->getTimer()->getTime();
	etapa = ETAPA_INTRO_AVI; 
}

void VRScreenStartUp::close() {

}

void VRScreenStartUp::render() {
	u32 timeNow;
	bool piscante=false, exibir=true;
	timeNow = VRSystem::getInstance()->getDevice()->getTimer()->getTime();

	sprintf(texto, "Cr�ditos - %d", VRGame::getInstance()->getCredits() );
	VRSystem::getInstance()->writeText(texto, 0, 0);
	sprintf(texto, " 1 = Cr�ditos, 2 = Start");
	VRSystem::getInstance()->writeText(texto, 0, 20);

	switch (etapa) {
	case ETAPA_INTRO_AVI:
		sprintf(texto, "Renderizando filme intro.avi - %d", (int) ((timeNow
				- lastTime)/1000) );
		if (timeNow - lastTime > TEMPO_SEGUNDOS_INTRO_AVI * 1000) {
			lastTime = timeNow;
			etapa = ETAPA_TEXTO_PISCANTE;
		}
		break;

	case ETAPA_TEXTO_PISCANTE:
		sprintf(texto, "Insira cr�ditos para jogar");
		piscante = true;
		if (timeNow - lastTime > TEMPO_SEGUNDOS_TEXTO_PISCANTE * 1000) {
			lastTime = timeNow;
			etapa = ETAPA_DEMO_AVI;
		}
		break;

	case ETAPA_DEMO_AVI:
		sprintf(texto, "Renderizando filme demo.avi - %d", (int) ((timeNow
				- lastTime)/1000));
		if (timeNow - lastTime > TEMPO_SEGUNDOS_DEMO_AVI * 1000) {
			lastTime = timeNow;
			etapa = ETAPA_INTRO_AVI;
		}
		break;
	}
	if (piscante)
		exibir = (timeNow-lastTime) % 1000 > 300 ? true : false;

	if (exibir)
		VRSystem::getInstance()->writeText(texto, 100, 100);

}

void VRScreenStartUp::OnInputEvent(int playerNum, int key, bool pressed,
		bool shiftState) {
	//printf("\nkey code is %d \n", key); fflush(stdout);
	VRScreen::OnInputEvent(playerNum, key, pressed, shiftState);

	if ( (key == VR_KEY_START)) {
		if (VRGame::getInstance()->getCredits()>0) {
			VRGame::getInstance()->addNewPlayer(playerNum);
			VRSystem::getInstance()->getScreenManager().setCurrentScreen("selectMusic");
			VRGame::getInstance()->setMusicSelectorPlayer(playerNum);
		}		
	}	
}
