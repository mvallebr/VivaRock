#ifndef _VR_SCENENODE_H_
#define _VR_SCENENODE_H_

#include <irrlicht.h>
using namespace irr;

class SceneNode : public scene::ISceneNode {
private:
	core::aabbox3d<f32> Box;
	video::S3DVertex Vertices[4];
	video::SMaterial Material;
public:
	scene::ISceneNodeAnimator* anim;
	scene::ISceneNodeAnimator* anim2;
	
	SceneNode(scene::ISceneNode* parent, scene::ISceneManager* mgr, s32 id);
	virtual ~SceneNode();
	
	virtual void OnRegisterSceneNode();
	virtual void render();
	virtual const core::aabbox3d<f32>& getBoundingBox() const ;
	virtual s32 getMaterialCount();
	virtual video::SMaterial& getMaterial(s32 i);
	
};

#endif /*_VR_SCENENODE_H_*/
