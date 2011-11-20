#include <screens/vrRenderNode.h>
#include <system/vrSystem.h>
#include <core/vrGame.h>

VRRenderNode::VRRenderNode(ITexture *image,
		vector3df center, int w, int h, unsigned long milisecondsOffset) {
	
	this->milisecondsOffset=milisecondsOffset;
	
	//Sets the image
	this->image = image;

	//Sets material information	
	material.setTexture(0, image);
	material.Wireframe = false;
	material.Lighting = false;
	material.MaterialType
			= video::EMT_TRANSPARENT_ALPHA_CHANNEL;

	//creates 3d object to be rendered
	horizontal = vector3df(w, 0, 0);
	vertical = vector3df(0, h, 0);
	this->setPosition(center);

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

VRRenderNode::~VRRenderNode() {
}

void VRRenderNode::setPosition(vector3df center) {
	this->center = center;
	guitarv[0].Pos = center + horizontal/2 + vertical/2;
	guitarv[1].Pos = center + horizontal/2 - vertical /2;
	guitarv[2].Pos = center - horizontal/2 - vertical/2;
	guitarv[3].Pos = center - horizontal/2 + vertical/2;
}
void VRRenderNode::draw(ISceneManager* smgr) {
	static u16 indices[] = { 0, 1, 2, 0, 2, 3 };

	video::IVideoDriver* driver = smgr->getVideoDriver();
	driver->setMaterial(material);
	core::matrix4 mat;
	driver->setTransform(video::ETS_WORLD, mat);

	// add the triangle faces. 
	// direction of rotation says which side 	
	driver->drawIndexedTriangleList(&guitarv[0], 4,
			&indices[0], 2);

}

