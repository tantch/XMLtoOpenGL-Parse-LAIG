/*
 * Flag.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: pim
 */

#include "Flag.h"

Flag::Flag() {
	// TODO Auto-generated constructor stub
	plane= new Plane(100);
	shader= new ShaderFlag();
}

Flag::~Flag() {
	// TODO Auto-generated destructor stub
}
void Flag::draw(){
	shader->bind();
	plane->draw();
	shader->unbind();

}
void Flag::draw(textureSt *t){
	draw();
}

