#include <screens/vrScreenTest3d.h>
#include <system/vrSystem.h>

using core::vector3df;
using irr::video::S3DVertex;

VRScreenTest3d::VRScreenTest3d(string name) :
	VRScreen(name) {
}

VRScreenTest3d::~VRScreenTest3d() {
}

void VRScreenTest3d::open() {
	string fname;
	//open background -- get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	smgrNotes = smgr->createNewSceneManager();
	smgr->clear();
	smgrNotes->clear();
	fname = VRSystem::getInstance()->getAppDir();
	fname += "media/difficultSelection.irr";
	printf("Loading irr file from '%s'\n", fname.c_str());
	fflush(stdout);
	smgr->loadScene(fname.c_str());

	//open textures
	fname = VRSystem::getInstance()->getAppDir();
	fname += "media/guitarra.png";
	printf("Loading png file from '%s'\n", fname.c_str());
	fflush(stdout);
	imgGuitarra = VRSystem::getInstance()->getDriver()->getTexture(fname.c_str());
	if (!(imgGuitarra)) {
		fprintf(stderr, "Could't load image!!!\n");
		fflush(stderr);
		quitApp();
	}
	// ------------------------------------------------------------------------
	//gets irr camera
	camera = smgr->getActiveCamera();

	printf("irr camera pos = (%f,%f,%f)\n",
			camera->getPosition().X, camera->getPosition().Y, camera->getPosition().Z);
	printf("irr camera target = (%f,%f,%f)\n",
			camera->getTarget().X, camera->getTarget().Y, camera->getTarget().Z);
	//camera->setTarget(core::vector3df(0, 0, 20));

	// ------------------------------------------------------------------------
	//sets up notes view

	//Camera
	//camera = smgrNotes->addCameraSceneNode(0, vector3df(0, -50, -350), vector3df(0, 0, 0));
	camera = smgrNotes->addCameraSceneNode(0, vector3df(0, 0, -350), vector3df(0, 0, 0));
	camera->setUpVector(vector3df(0, 1, 0));

	//Sets material information	
	material.setTexture(0, imgGuitarra);
	material.Wireframe = false;
	material.Lighting = false;
	material.MaterialType
			= video::EMT_TRANSPARENT_ALPHA_CHANNEL;

	// set the position
	vector3df origin;
	vector3df center = origin + vector3df(0, 50, 0);
	origin = center + vector3df(-300, 0, 0);
	initGuitarVertices(origin, &guitar1v[0]);
	origin = center + vector3df(-100, 0, 0);
	initGuitarVertices(origin, &guitar2v[0]);
	origin = center + vector3df(100, 0, 0);
	initGuitarVertices(origin, &guitar3v[0]);
}

void VRScreenTest3d::initGuitarVertices(vector3df origin,
		S3DVertex *guitarv) {
	//creates 3d object to be rendered
	vector3df horizontal = vector3df(200, 0, 0);
	vector3df offsetH = vector3df(0, 0, 0);
	vector3df vertical = vector3df(0, 480, 0);
	guitarv[0].Pos = origin + horizontal + vertical/2;
	guitarv[1].Pos = origin + horizontal + offsetH
			- vertical /2;
	guitarv[2].Pos = origin - offsetH - vertical/2;
	guitarv[3].Pos = origin + vertical/2;

	// set texture coords 
	guitarv[0].TCoords.set(0.0f, 0.0f);
	guitarv[0].Color = video::SColor(255, 255, 255, 255);
	guitarv[1].TCoords.set(0.0f, 1.0f);
	guitarv[1].Color = video::SColor(255, 255, 255, 255);
	guitarv[2].TCoords.set(1.0f, 1.0f);
	guitarv[2].Color = video::SColor(255, 255, 255, 255);
	guitarv[3].TCoords.set(1.0f, 0.0f);
	guitarv[3].Color = video::SColor(255, 255, 255, 255);
}

void VRScreenTest3d::close() {

}

void VRScreenTest3d::render() {
	//get scene manager
	scene::ISceneManager* smgr = VRSystem::getInstance()->getSceneManager();
	smgr->drawAll();
	smgrNotes->drawAll();

	video::IVideoDriver* driver =
			smgrNotes->getVideoDriver();
	driver->setMaterial(material);
	core::matrix4 mat;
	driver->setTransform(video::ETS_WORLD, mat);

	// add the triangle faces. 
	// direction of rotation says which side 
	u16 indices[] = { 0, 1, 2, 0, 2, 3 };
	driver->drawIndexedTriangleList(&guitar1v[0], 4,
			&indices[0], 2);
	driver->drawIndexedTriangleList(&guitar2v[0], 4,
			&indices[0], 2);
	driver->drawIndexedTriangleList(&guitar3v[0], 4,
			&indices[0], 2);
}

void VRScreenTest3d::OnInputEvent(int playerNum, int key,
		bool pressed, bool shiftState) {
	VRScreen::OnInputEvent(playerNum, key, pressed,
			shiftState);

}
