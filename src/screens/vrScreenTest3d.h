#ifndef VRSCREENTEST3D_H_
#define VRSCREENTEST3D_H_

#include <system/vrScreen.h>
#include <system/sceneNode.h>
#include <core/vrPlayer.h>

#include <irrlicht.h>
using namespace irr;
using irr::video::ITexture;
using core::vector3df;
using irr::video::S3DVertex;

class VRScreenTest3d : public VRScreen {
private:		
	scene::ICameraSceneNode* camera;
	video::S3DVertex guitar1v[4], guitar2v[4], guitar3v[4];
	video::SMaterial material;
	scene::ISceneManager* smgrNotes;
	ITexture *imgGuitarra;
public:
	VRScreenTest3d(string name);
	virtual ~VRScreenTest3d();

	void initGuitarVertices(vector3df origin, S3DVertex *guitarv) ;
	
	virtual void open();
	void close();
	virtual void render();
	virtual void OnInputEvent(int playerNum, int key, bool pressed,
			bool shiftState);

};

#endif /*VRSCREENTEST3D_H_*/
