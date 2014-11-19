/*
 * Vehicle.cpp
 *
 *  Created on: Nov 19, 2014
 *      Author: pim
 */

#include "Vehicle.h"

Vehicle::Vehicle() {
	vector< vector< float > > ctrlPoints;
	vector<float> temp;

	temp.push_back(0);
	temp.push_back(0);
	temp.push_back(0);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(4);
	temp.push_back(2);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(0);
	temp.push_back(2);
	temp.push_back(2);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(1);
	temp.push_back(0);
	temp.push_back(0);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(1);
	temp.push_back(4);
	temp.push_back(1);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(1);
	temp.push_back(2);
	temp.push_back(2);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(2);
	temp.push_back(0);
	temp.push_back(0);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(2);
	temp.push_back(4);
	temp.push_back(1);
	ctrlPoints.push_back(temp);
	temp.clear();
	temp.push_back(2);
	temp.push_back(2);
	temp.push_back(2);
	ctrlPoints.push_back(temp);
	temp.clear();
	capa=  new Patch(2,100,100,"fill",ctrlPoints);
	corpo= new SphereSt(1,20,20);
	bracoD= new CylinderSt(0.1,0.1,1.7,20,20);
	bracoE= new CylinderSt(0.1,0.1,1.7,20,20);
	pernaE= new CylinderSt(0.1,0.1,1,20,20);
	pernaD= new CylinderSt(0.1,0.1,1,20,20);


}
void Vehicle::draw(){

	glPushMatrix();
	glTranslatef(-1,1.3,-2.3);
	capa->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,3,0);
	corpo->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5,3,0);
	bracoD->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5,3,0);
	bracoE->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-0.5,2.4,-0.2);
	glRotatef(90,1,0,0);
	pernaD->draw();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.5,2.4,-0.2);
	glRotatef(90,1,0,0);
	pernaE->draw();
	glPopMatrix();


}
void Vehicle::draw(textureSt *t){
	draw();
}

Vehicle::~Vehicle() {
	// TODO Auto-generated destructor stub
}

