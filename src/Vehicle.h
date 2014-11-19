/*
 * Vehicle.h
 *
 *  Created on: Nov 19, 2014
 *      Author: pim
 */
#ifndef SRC_VEHICLE_H_
#define SRC_VEHICLE_H_
#include "dataStructs.h"
#include "Patch.h"


class Vehicle :public PrimSt{
public:
	Vehicle();
	virtual ~Vehicle();
	Patch* capa;
	SphereSt* corpo;
	CylinderSt* pernaE;
	CylinderSt* pernaD;
	CylinderSt* bracoE;
	CylinderSt* bracoD;
	void draw();
	void draw(textureSt *t);
};

#endif /* SRC_VEHICLE_H_ */
