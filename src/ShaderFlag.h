/*
 * Shader.h
 *
 *  Created on: Nov 18, 2014
 *      Author: pim
 */

#ifndef SRC_SHADERFLAG_H_
#define SRC_SHADERFLAG_H_
#include "CGFshader.h"
#include "CGFtexture.h"
#include "CGFapplication.h"
class ShaderFlag:public CGFshader {
public:

	ShaderFlag(string texture);
	~ShaderFlag();
	virtual void bind();
	virtual void unbind();
	float angle;
	unsigned long startTime;
	float time;
	float wind;
	int windLoc;
	int angleLoc;
	int timeLoc;
	int baseTextLoc;
	void update(unsigned long t,int wind);
	CGFtexture * baseTexture;

};

#endif /* SRC_SHADERFLAG_H_ */
