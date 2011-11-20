#include <screens/vrScreenGame.h>
#include <system/vrSystem.h>

using core::vector3df;
using irr::video::S3DVertex;

VRScreenGame::VRScreenGame(string name) :
	VRScreen(name) {
	soundsStarted=false;
	//delete player sounds
	for (int i=0; i<3; i++) {
		playerSound[i] = NULL;
	}
}

VRScreenGame::~VRScreenGame() {
}

void VRScreenGame::open() {
	string fname;
	//TEMP
	VRGame::getInstance()->selectMusic("musica1");
	VRGame::getInstance()->selectdifficult(1);
	VRGame::getInstance()->setPlayer(0, new VRPlayer());
	//	VRGame::getInstance()->setPlayer(1, new VRPlayer());
	//	VRGame::getInstance()->setPlayer(2, new VRPlayer());
	// ------------------------------------------------------------------------
	// initial state
	points = 0;
	elapsedMiliSeconds = 0;
	lastMiliSec = 0;
	for (int i=0; i<MAX_NUMBER_OF_PLAYERS; i++)
		lastChord[i] = 0;
	lastAccMiliSec =0;
	// ------------------------------------------------------------------------
	//open background -- get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	fname = VRSystem::getInstance()->getAppDir();
	fname = fname + "media/" + VRGame::getInstance()->getCurrentScenario()->getIrrFile();
	printf("Loading irr file from '%s'\n", fname.c_str());
	fflush(stdout);
	// ------------------------------------------------------------------------
	//sets up notes view
	//Creates new scene manager
	smgrNotes = smgr->createNewSceneManager();
	smgr->clear();
	smgrNotes->clear();
	smgr->loadScene(fname.c_str());
	// ------------------------------------------------------------------------
	//open textures
	fname = VRSystem::getInstance()->getAppDir();
	fname += "media/"+ VRGame::getInstance()->getCurrentScenario()->getGuitarra().imageFilename;
	printf("Loading png file from '%s'\n", fname.c_str());
	fflush(stdout);
	imgGuitarra = VRSystem::getInstance()->getDriver()->getTexture(fname.c_str());
	if (!(imgGuitarra)) {
		fprintf(stderr, "Could't load image!!!\n");
		fflush(stderr);
		quitApp();
	}
	for (int i=0; i<5; i++) {
		fname = VRSystem::getInstance()->getAppDir();
		fname += "media/"+ VRGame::getInstance()->getCurrentScenario()->getNotas(i).imageFilename;
		printf("Loading png file from '%s'\n",
				fname.c_str());
		fflush(stdout);
		imgNotas[i] = VRSystem::getInstance()->getDriver()->getTexture(fname.c_str());
		if (!(imgNotas[i])) {
			fprintf(stderr, "Could't load image!!!\n");
			fflush(stderr);
			quitApp();
		}
	}
	//Camera
	//vector3df pos = vector3df(0, -150, -316);
	vector3df pos = vector3df(0, -403, -200);
	//vector3df pos = vector3df(0, 0, -350);
	vector3df target = vector3df(0, 0, 0);
	camera = smgrNotes->addCameraSceneNode(0, pos, target);
	camera->setUpVector(vector3df(0, 1, 0));
	// set the guitar positions
	vector3df origin;
	vector3df center = vector3df(0, 50, 0);
	origin = center + vector3df(-VRGame::getInstance()->getCurrentScenario()->getGuitarra().leftOffset, 0, 0);
	guitarP1 = new VRRenderNode(imgGuitarra, origin, imgGuitarra->getSize().Width, imgGuitarra->getSize().Height, 0);
	//initGuitarVertices(origin, &guitar1v[0]);
	origin = center + vector3df(0, 0, 0);
	//initGuitarVertices(origin, &guitar2v[0]);
	guitarP2 = new VRRenderNode(imgGuitarra, origin, imgGuitarra->getSize().Width, imgGuitarra->getSize().Height, 0);
	origin = center + vector3df(VRGame::getInstance()->getCurrentScenario()->getGuitarra().leftOffset, 0, 0);
	//initGuitarVertices(origin, &guitar3v[0]);
	guitarP3 = new VRRenderNode(imgGuitarra, origin, imgGuitarra->getSize().Width, imgGuitarra->getSize().Height, 0);
	// ------------------------------------------------------------------------
	//open sounds	
	//For each player
	for (int i=0; i< MAX_NUMBER_OF_PLAYERS; i++) {
		playerSound[i] = NULL;
		if (VRGame::getInstance()->getPlayer(i)!=NULL) {
			playerSound[i]
					= VRGame::getInstance()->getSelectedMusic()->getTrackSoundByTrackType(getPlayerTrack(i));
		}
	}

	for (unsigned int i=0; i< VRGame::getInstance()->getSelectedMusic()->getNumberOfSounds(); i++) {
		sounds.insert(sounds.end(), VRGame::getInstance()->getSelectedMusic()->getMusicSound(i));
	}
	soundsStarted=false;
	// ------------------------------------------------------------------------
	//Starts the timer
	//VRSystem::getInstance()->getDevice()->getTimer()->start();
}
void VRScreenGame::startSounds() {
	if (soundsStarted)
		return;
	soundsStarted=true;
	//start sounds
	for (unsigned int i=0; i< sounds.size(); i++) {
		VRSound *snd = sounds.at(i);
		snd->start();
	}
	//start player sounds
	for (int i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		if (VRGame::getInstance()->getPlayer(i)!=NULL) {
			if (playerSound[i]!=NULL) {
				playerSound[i]->start();
			}
		}
	}
}
void VRScreenGame::close() {
	//delete sounds
	for (unsigned int i=0; i< sounds.size(); i++) {
		VRSound *snd = sounds.at(i);
		snd->pause();
		snd->stop();
		delete snd;
	}
	sounds.clear();
	//delete player sounds
	for (int i=0; i<3; i++) {
		if (playerSound[i]!=NULL) {
			delete playerSound[i];
			playerSound[i] = NULL;
		}
	}

	//delete images
	delete imgGuitarra;
	delete imgNotas[0];
	delete imgNotas[1];
	delete imgNotas[2];
	delete imgNotas[3];
	delete smgrNotes;
	delete smgrGuitars;
	delete camera;
	//VRSystem::getInstance()->getDevice()->getTimer()->stop();
}

void VRScreenGame::updateNotesPositions(int playerNum,
		unsigned long elapsedMiliSecondsFromLast) {
	VRScenario *scenario = VRGame::getInstance()->getCurrentScenario();
	for (int i=0; i<3; i++) {
		vector<VRRenderNode *>::iterator it;
		for (it = notesP[i].begin(); it != notesP[i].end(); ++it) {
			VRRenderNode *renderNode = *it;
			float delta = (elapsedMiliSeconds
					- renderNode->getMilisecondsOffset())
					* scenario->getOffsetColisaoNotas()
					/ scenario->getOffsetTopoApertoBotao();
			vector3df pos = getNotesOrigin(playerNum)
					+vector3df(0, -delta, 0);
			pos.X = renderNode->getPosition().X;
			renderNode->setPosition(pos);
			//printf("y = %lf \n", position.Y);
		}
	}
}

void VRScreenGame::render() {
	unsigned long miliSec, delta;

	int difficult = VRGame::getInstance()->getCurrentDifficult();
	//VRScenario *scenario = VRGame::getInstance()->getCurrentScenario();
	// --------------------------------------------------------------------------
	//Calculates elapser mili seconds since game begin
	if (lastMiliSec==0) {
		lastMiliSec = VRSystem::getInstance()->getDevice()->getTimer()->getRealTime();
		gameStartMilisec = lastMiliSec;
	}
	// --------------------------------------------------------------------------
	//Updates current milisec
	miliSec = VRSystem::getInstance()->getDevice()->getTimer()->getRealTime();
	delta=miliSec-lastMiliSec;
	elapsedMiliSeconds += delta;
	if (delta>0)
		lastMiliSec = miliSec;

	//	printf("milisec = %ld lastMilisec = %ld\n", miliSec,
	//			lastMiliSec);

	// --------------------------------------------------------------------------
	//Checks if sound should start
	if (miliSec - gameStartMilisec >= VRGame::getInstance()->getSelectedMusic()->getTimeOffset()) {
		if (!soundsStarted)
			startSounds();
	}
	// --------------------------------------------------------------------------
	//For each player
	for (int playerNum=0; playerNum< MAX_NUMBER_OF_PLAYERS; playerNum++) {
		VRPlayer *player = VRGame::getInstance()->getPlayer(playerNum);
		if (player==NULL)
			continue;

		VRMusicTrack *track = VRGame::getInstance()->getSelectedMusic()->getTrack(getPlayerTrack(playerNum));
		if (track==NULL) {
			fprintf(stderr, "Error, player has no correspondent track!\n");
			fflush(stdout);
			exit(-5);
		}
		// --------------------------------------------------------------------------
		//Updates notes positions for player	
		if (delta>0)
			updateNotesPositions(playerNum, delta);

		// --------------------------------------------------------------------------
		//Checks if some note needs to be created		
		for (unsigned int i=lastChord[playerNum]; i
				<track->getNumberOfChords(difficult); i++) {
			VRChord *chord = track->getChord(difficult, i);
			if (chord->getMiliSecondsFromBeginning()
					<=elapsedMiliSeconds) {
				//Create note			
				vector3df origin =
						getNotesOrigin(playerNum);
				for (int i=0; i<4; i++) {
					if (chord->getNote(i)) {
						vector3df
								noteCenter =
										origin
												+ vector3df(
														VRGame::getInstance()->getCurrentScenario()->getNotas(i).leftOffset,
														0,
														0);
						VRRenderNode
								*rn =
										new VRRenderNode(imgNotas[i], noteCenter ,
												imgNotas[i]->getSize().Width,
												imgNotas[i]->getSize().Height, chord->getMiliSecondsFromBeginning());
						rn->setNoteIndex(i);
						notesP[playerNum].insert(
								notesP[playerNum].end(), rn);
					}
				}
				lastChord[playerNum]++;
			} else {
				break;
			}
		}
		// --------------------------------------------------------------------------
		//Checks if some note needs to be deleted
		vector<VRRenderNode *>::iterator it;
		for (it = notesP[playerNum].begin(); it
				!= notesP[playerNum].end();) {
			VRRenderNode *renderNode = *it;
			if (renderNode->getPosition().Y < -imgGuitarra->getSize().Height) {
				notesP[playerNum].erase(it);
				delete renderNode;
			} else {
				++it;
			}
		}
	}
	// --------------------------------------------------------------------------
	// Draws background
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	smgr->drawAll();
	// --------------------------------------------------------------------------
	// Draws guitars	
	//smgrNotes->clear();
	smgrNotes->drawAll();
	//VRSystem::getInstance()->getDriver()->clearZBuffer();
	guitarP1->draw(smgrNotes);
	guitarP2->draw(smgrNotes);
	guitarP3->draw(smgrNotes);
	// --------------------------------------------------------------------------
	// Draws notes
	for (int i=0; i<MAX_NUMBER_OF_PLAYERS; i++) {
		vector<VRRenderNode *>::iterator it;
		for (it = notesP[i].begin(); it != notesP[i].end(); ++it) {
			VRRenderNode *renderNode = *it;
			renderNode->draw(smgrNotes);
		}
	}
}

void VRScreenGame::OnInputEvent(int playerNum, int key,
		bool pressed, bool shiftState) {
	VRScreen::OnInputEvent(playerNum, key, pressed,
			shiftState);
	VRScenario *scenario = VRGame::getInstance()->getCurrentScenario();

	// --------------------------------------------------------------------------
	//Checks if some note needs to be deleted
	//	printf(	"elapsedMiliSeconds = %ld min=%ld max=%ld \n renderNode->getMilisecondsOffset() = ",
	//			elapsedMiliSeconds,	elapsedMiliSeconds	- scenario->getErro2OffsetTopoApertoBotao() ,
	//			elapsedMiliSeconds	+ scenario->getErro2OffsetTopoApertoBotao() );
	//For each player
	for (int i=0; i<3; i++) {
		vector<VRRenderNode *>::iterator it;
		if (i!= playerNum)
			continue;
		//for each note
		bool flagX=false, flagZ=false, flagC=false, flagV=
				false;
		for (it = notesP[i].begin(); it != notesP[i].end();) {
			VRRenderNode *renderNode = *it;
			//check where it hit
			bool shouldDelete=false;
			//printf("%ld ", renderNode->getMilisecondsOffset()+ scenario->getOffsetTopoApertoBotao());
			if ((renderNode->getMilisecondsOffset()
					+ scenario->getOffsetTopoApertoBotao()
					> elapsedMiliSeconds
							- scenario->getErro1OffsetTopoApertoBotao() )
					&& (renderNode->getMilisecondsOffset()
							+ scenario->getOffsetTopoApertoBotao()
							< elapsedMiliSeconds
									+ scenario->getErro1OffsetTopoApertoBotao() )) {
				//Acertou em cheio
				shouldDelete=true;
				//TODO: incrementa pontos
			} else if ((renderNode->getMilisecondsOffset()
					+ scenario->getOffsetTopoApertoBotao()
					> elapsedMiliSeconds
							- scenario->getErro2OffsetTopoApertoBotao() )
					&& (renderNode->getMilisecondsOffset()
							+ scenario->getOffsetTopoApertoBotao()
							< elapsedMiliSeconds
									+ scenario->getErro2OffsetTopoApertoBotao() )) {
				//Quase acertou
				shouldDelete=true;
				//TODO: incrementa pontos
			}
			//checks keyboard
			if (shouldDelete) {
				//Once it had hit within position range, check if player hit right KEY
				if ((key == VR_KEY_Z)
						&& renderNode->getNoteIndex()==0) {
					shouldDelete=!flagZ;
					flagZ=true;
				} else if ((key == VR_KEY_X)
						&& renderNode->getNoteIndex()==1) {
					shouldDelete=!flagX;
					flagX=true;
				} else if ((key == VR_KEY_C)
						&& renderNode->getNoteIndex()==2) {
					shouldDelete=!flagC;
					flagC=true;
				} else if ((key == VR_KEY_V)
						&& renderNode->getNoteIndex()==3) {
					shouldDelete=!flagV;
					flagV=true;
				} else {
					shouldDelete=false;
					//TODO play error sound
					//Sets volume to 1/3					
					if (playerSound[playerNum]!=NULL) {
						playerSound[playerNum]->setVolume(playerSound[playerNum]->getMaxVolume()/7);
					}
				}
				//The key was also right
				if (shouldDelete) {
					//sets volume to the max
					if (playerSound[playerNum]!=NULL) {
						playerSound[playerNum]->setVolume(playerSound[playerNum]->getMaxVolume());
					}
				}
			}
			//delete condition
			if (shouldDelete) {
				notesP[i].erase(it);
				delete renderNode;
			} else {
				++it;
			}
		}

		//printf("\n");
		fflush(stdout);
	}
}

