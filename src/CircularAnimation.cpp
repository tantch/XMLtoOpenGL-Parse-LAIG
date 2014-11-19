/*
 * CircularAnimation.cpp
 *
 *  Created on: 18/11/2014
 *      Author: vania
 */

#include "CircularAnimation.h"

CircularAnimation::CircularAnimation() {
	// TODO Auto-generated constructor stub

}

CircularAnimation::CircularAnimation(string id, float span, vector<float> center, float radius, float initAngle, float rotAngle)
:Animation(id,span){

	this->center=center;
	this->radius=radius;
	this->initAngle=initAngle;
	this->rotAngle=rotAngle;
	x=0;
	y=0;
	z=0;
	Angle=0;
	lastAngle=0;
}

void CircularAnimation::update(unsigned long t){

	if(!isFinished){
		if(firstTime){
			firstTime=false;
			startTime=t;
			lastTime=t;
		}
		else{
			unsigned long interval=t-startTime;
			float currentSpan = (float) (t - startTime) / 1000;
			if (span < currentSpan)
				isFinished = true;
			Angle=angularSpeed/t;
			lastTime=t;
		}
	}

}

void CircularAnimation::calculateSpeed(){
	distance=2*PI*radius;
	speed=distance/span;
	angularSpeed=rotAngle/span;


}

void CircularAnimation::move(){
	glRotated(Angle, 0,1,0);
	glTranslated(radius,0.0,0.0);
}

void CircularAnimation::reset(){

}
CircularAnimation::~CircularAnimation() {
	// TODO Auto-generated destructor stub
}

