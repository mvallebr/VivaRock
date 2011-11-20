#include <screens/vrScreenTest.h>
#include <system/vrSystem.h>

VRScreenTest::VRScreenTest(string name) : VRScreen(name) {
}

VRScreenTest::~VRScreenTest() {
}

void VRScreenTest::open() {
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	//add camera		
	camera = smgr->addCameraSceneNode(0, core::vector3df(0,
			0, -300), core::vector3df(0, 0, 0));
	camera->OnRegisterSceneNode();
	camera2 = smgr->addCameraSceneNode(0, core::vector3df(
			0, 1600, -300), core::vector3df(0, 0, 0));
	//camera = smgr->addCameraSceneNodeFPS();
	//camera->addAnimator(smgr->createFlyCircleAnimator(core::vector3df(0, -120, 0), 70, 0.002, core::vector3df(0.01f, 0.01f, 0.01f)));
	camera->addAnimator(smgr->createRotationAnimator(core::vector3df(
			0, 1, 0)));
	//Add custom mesh
	scene::IAnimatedMesh* mesh =
			smgr->getMesh("../media/Demon.md2");
	scene::IAnimatedMeshSceneNode* node =
			smgr->addAnimatedMeshSceneNode(mesh);
	if (node) {
		node->setPosition(core::vector3df(0, 0, 500));
		node->setMaterialFlag(video::EMF_LIGHTING, false);
		node->setFrameLoop(0, 310);
		node->setMaterialTexture( 0, VRSystem::getInstance()->getDriver()->getTexture("../media/Skindemon.pcx") );
		//node->addAnimator(smgr->createFlyCircleAnimator(core::vector3df(0, -120, 0), 70, 0.002, core::vector3df(0.01f, 0.01f, 0.01f)));
	}

	//adds custom scene node
	myNode = new SceneNode(smgr->getRootSceneNode(), smgr, 666);
	//myNode->setPosition(core::vector3df(70.0f, 0, 0));
	myNode->drop();
	//Adds rotation animation
	myNode->anim
			= smgr->createRotationAnimator(core::vector3df(
					1.0f, 0.1f, 0.1f));
	//myNode->addAnimator(myNode->anim);
	myNode->anim->drop();

	//Adds movement animation

	{
		smgr->setActiveCamera(camera);
		enum {DRAW_DISTANCE = 100 /* adjust empirically based on the desired model size on screen */};
		core::position2di
				topScreenPosition(0, 0/* set the desired top screen position */);
		core::position2di
				bottomScreenPosition(700, 400/* set the desired bottom screen position */);
		core::line3df topRay =
				smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
						topScreenPosition,
						smgr->getActiveCamera());
		core::line3df bottomRay =
				smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
						bottomScreenPosition,
						smgr->getActiveCamera());
		core::vector3df top3DPosition = topRay.start
				+ (topRay.getVector().normalize() * DRAW_DISTANCE);
		core::vector3df bottom3DPosition = bottomRay.start
				+ (bottomRay.getVector().normalize() * DRAW_DISTANCE);

		printf("%.2f %.2f %.2f <-> %.2f %.2f %.2f \n",
				top3DPosition.X, top3DPosition.Y,
				top3DPosition.Z, bottom3DPosition.X,
				bottom3DPosition.Y, bottom3DPosition.Z);
		fflush(stdout);
		myNode->anim2
				= smgr->createFlyStraightAnimator(
						//core::vector3df(0, 100, 50), core::vector3df(0, -100, 50), 
						top3DPosition, bottom3DPosition,
						4000, true);
		//myNode->addAnimator(myNode->anim2);
		myNode->anim2->drop();
	}
	myNode->setPosition(core::vector3df(0, 0, 200));
	camera->addChild(myNode);

	//myNode->setPosition(camera->getTarget()+camera->getPosition());


	time = VRSystem::getInstance()->getDevice()->getTimer()->getTime();
}

void VRScreenTest::close() {

}

void VRScreenTest::render() {
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	//smgr->setActiveCamera(camera);		
	camera->setTarget(myNode->getAbsolutePosition());
	smgr->drawAll();
	//		VRSystem::getInstance()->getDriver()->beginScene(false, true, irr::video::SColor(255, 255, 255, 255));
	//		smgr->setActiveCamera(camera2);		
	//		smgr->drawAll();

	sprintf(
			texto,
			"Viva rock - position: %.1f    time: %u ----- %f %f %f",
			myNode->getPosition().X, VRSystem::getInstance()->getDevice()->getTimer()->getTime() - time,
			//(camera->get), 
			(camera->getTarget()-camera->getPosition()).X, (camera->getTarget()-camera->getPosition()).Y, (camera->getTarget()-camera->getPosition()).Z);
	VRSystem::getInstance()->writeText(texto, 0, 0);

	//myNode->setPosition(camera->getPosition() + (camera->getTarget()-camera->getPosition())/2 );		

	//		if ((myNode->getPosition().X < 20) && (myNode->getPosition().X > -20)) {
	//			core::vector3df position = myNode->getPosition();
	//			position.X -=  0.1;//20 *(VRSystem::getInstance()->getDevice()->getTimer()->getTime() - time)/1000;
	//			myNode->setPosition(position);
	//			//myNode->anim2->animateNode(myNode, VRSystem::getInstance()->getDevice()->getTimer()->getTime() - time);			
	//			myNode->setVisible(false);
	//		} else {
	//			myNode->setVisible(true);
	//		}
	if ((VRSystem::getInstance()->getDevice()->getTimer()->getTime() - time)>0)
		time = VRSystem::getInstance()->getDevice()->getTimer()->getTime();
}

void VRScreenTest::OnInputEvent(int playerNum, int key, bool pressed,
		bool shiftState) {

}
