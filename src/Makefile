
OBJS=	main.o \
	system/vrSystem.o system/vrGameLoop.o system/sceneNode.o \
	system/vrScreenManager.o system/vrEventReceiver.o \
	system/vrScreen.o system/vrSound.o \
	screens/vrScreenTest.o screens/vrScreenTest3d.o		screens/vrScreenSelectMusic.o \
	screens/vrScreenSelectDifficult.o  screens/vrScreenGame.o \
	screens/vrScreenStartUp.o screens/vrRenderNode.o \
	core/vrGame.o core/vrScenario.o core/vrMusic.o core/vrMusicTrack.o \
	core/vrPlayer.o core/vrChord.o
	
	
CXX=c++
IRRLICHT_DIR=C:/pastas/devEnv/irrlicht-1.5.1
IRR_CPPFLAGS=-I$(IRRLICHT_DIR)/include
IRR_LDFLAGS=-L$(IRRLICHT_DIR)/lib/Win32-gcc -lIrrlicht

SDL_FFMPEG_DIR=C:/pastas/devEnv/SDL_ffmpeg-0.7.0
SDL_FFMPEG_CPPFLAGS=-I$(SDL_FFMPEG_DIR)/include
SDL_FFMPEG_LDFLAGS=-L$(SDL_FFMPEG_DIR)/lib -lSDL_ffmpeg -lmingw32 -lwsock32

SDL_DIR=C:/pastas/devEnv/SDL-1.2.13
SDL_CPPFLAGS=-I$(SDL_DIR)/include
SDL_LDFLAGS=-L$(SDL_DIR)/lib -lSDLmain -lSDL  -Dmain=SDL_main -DWIN32 -Uunix -mno-cygwin

CPPFLAGS=-g -Wall -O2 $(IRR_CPPFLAGS) $(SDL_CPPFLAGS) -I.
#$(SDL_FFMPEG_CPPFLAGS)  
LDFLAGS=$(IRR_LDFLAGS)  $(SDL_LDFLAGS) 
#$(SDL_FFMPEG_LDFLAGS) 
PROGNAME=../bin/vivarock

all: $(OBJS)
	$(CXX)  $(OBJS) -o $(PROGNAME)  $(LDFLAGS) 

clean: 
	rm -f *.o *~ *.bak 
	cd core && rm -f *.o *~ *.bak 
	cd screens && rm -f *.o *~ *.bak 
	cd system && rm -f *.o *~ *.bak
	
purge: clean 
	rm -f $(PROGNAME).exe
	
