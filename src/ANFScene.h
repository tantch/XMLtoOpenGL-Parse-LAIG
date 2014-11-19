#ifndef DEMOSCENE_H
#define DEMOSCENE_H
#include "dataStructs.h"
#include "CGFscene.h"
#include "CGFshader.h"
#include "tinyxml.h"
#include "Flag.h"
#include "Plane.h"
#include "Patch.h"
class ANFScene: public CGFscene {
public:
	void init();
	void display();
	~ANFScene();
	ANFScene(char *filename);
	void update(unsigned long t);
	void setDisplayList(map<string, NodeSt>::iterator node,
			map<string, appearanceSt*>::iterator appearanceId, bool force);
	void activateLight(int id, bool enable);

	TiXmlDocument* doc;
	TiXmlElement* anfElement;
	TiXmlElement* globalElements;
	TiXmlElement* cameraElements;
	TiXmlElement* lightElements;
	TiXmlElement* textureElements;
	TiXmlElement* appearanceElements;
	TiXmlElement* graphElements;
	//globals
	unsigned int dlcount=1;
	int activeCam=0;
	int drawMode=0;
	int wind=1;
	drawingSt* draw;
	cullingSt* culling;
	lightingSt* lighting;
	cameraMp* cameras;
	lightMp* lights;
	textureMp* textures;
	appearanceMp* appearances;
	GraphMp* graph;
	vector<string> luzesId;
	vector<string> camerasId;
	Flag* flagtest;


};

#endif
