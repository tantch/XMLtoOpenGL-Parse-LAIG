/*
 * Plane.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: pim
 */

#include "Plane.h"

GLfloat ctrlpoints[4][3] = { { -0.5, 0.0, -0.5 }, { 0.5, 0.0, -0.5 }, { -0.5,
		0.0, 0.5 }, { 0.5, 0.0, 0.5 } };

GLfloat nrmlcompon[4][3] = { { 0.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 1.0,
		0.0 }, { 0.0, 1.0, 0.0 } };


GLfloat textpoints[4][2] = { { 0.0, 0.0 },  { 1.0, 0.0 },{ 0.0, 1.0 }, { 1.0,
		1.0 } };

Plane::Plane(int div) {
	this->divs = div;
}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

void Plane::draw() {

	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2,
			&ctrlpoints[0][0]);
	glMap2f(GL_MAP2_NORMAL, 0.0, 1.0, 3, 2, 0.0, 1.0, 6, 2, &nrmlcompon[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, 2, 0.0, 1.0, 4, 2,
			&textpoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_MAP2_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(divs, 0.0, 1.0, divs, 0.0, 1.0);
	glEvalMesh2(GL_FILL, 0, divs, 0, divs);

}
void Plane::draw(textureSt *t) {
	draw();
}

