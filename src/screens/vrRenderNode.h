#ifndef VRRENDERNODE_H_
#define VRRENDERNODE_H_


#include <irrlicht.h>
using namespace irr;
using irr::video::ITexture;
using core::vector3df;
using irr::video::S3DVertex;
using irr::video::SMaterial;
using irr::scene::ISceneManager;

class VRRenderNode
{	
private:
	ITexture *image;
	S3DVertex guitarv[4];
	SMaterial material;
	vector3df horizontal, vertical;
	vector3df center;	
	int noteIndex;
	unsigned long milisecondsOffset;
public:	
	void setPosition(vector3df center);
	inline vector3df getPosition() {
		return center;
	}
	void draw(ISceneManager* smgr);
	
	inline int getNoteIndex(){
		return noteIndex;
	}
	inline void setNoteIndex(int noteIndex){
		this->noteIndex = noteIndex;
	}
	inline void increaseMilisecondsOffset(unsigned long added) {
		milisecondsOffset += added;
	}
	inline unsigned long getMilisecondsOffset() {
		return milisecondsOffset;
	}
	inline S3DVertex * getGuitarVertices() {
		return guitarv;
	}
	inline ITexture *getImage() {
		return image;
	}
	
	VRRenderNode(ITexture *image, vector3df center, int w, int h, unsigned long milisecondsOffset);
	virtual ~VRRenderNode();
};

#endif /*VRRENDERNODE_H_*/
