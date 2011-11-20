#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <system/vrSystem.h>
#include <system/vrGameLoop.h>

int main(int argc, char *argv[]) {
	printf("VivaRock Initializing\n");
	VRGameLoop *g;
	int w= SCREEN_WIDTH;
	int h= SCREEN_HEIGHT;

	// Init system
	VRSystem *sys = VRSystem::getInstance();
	sys->init(argc, argv, w, h);

	//Run game loop	
	g = new VRGameLoop();
	g->init();
	g->run();
	g->destroy();

	//Destroy everything and quit
	sys->destroy();

	return 0;

}
