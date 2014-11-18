/*
 * Patch.cpp
 *
 *  Created on: Nov 18, 2014
 *      Author: pim
 */

#include "Patch.h"

#include "Patch.h"

Patch::Patch(int order, int partsU, int partsV, string compute,
		float ** cntrlPoints) {
	this->order = order;
	this->partsV = partsV;
	this->partsU = partsU;
	this->compute = compute;
	this->cntrlPoints = cntrlPoints;

	int n = (order + 1) * (order + 1);
	float inc = 1 / order;
	float x = 0, y = 0;

	textPoints = (float **) malloc(n * sizeof(float));

	for (int i = 0; i < n; i++) {
		textPoints[i] = (float*) malloc(sizeof(float) * 2);
		textPoints[i][0] = x;
		textPoints[i][1] = y;
		x += inc;
		if (x > 1) {
			x = 0;
			y += inc;
		}
	}

}

Patch::~Patch() {
	// TODO Auto-generated destructor stub
}

void Patch::draw() {
	glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, (order + 1), 0.0, 1.0,
			3 * (order + 1), (order + 1), &cntrlPoints[0][0]);
	glMap2f(GL_MAP2_TEXTURE_COORD_2, 0.0, 1.0, 2, (order + 1), 0.0, 1.0,
			2 * (order + 1), (order + 1), &textPoints[0][0]);

	glEnable(GL_MAP2_VERTEX_3);
	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_MAP2_TEXTURE_COORD_2);
	glMapGrid2f(partsU, 0.0, 1.0, partsV, 0.0, 1.0);
	if (compute == "fill")
		glEvalMesh2(GL_FILL, 0, partsU, 0, partsV);
	else if (compute == "line")
		glEvalMesh2(GL_LINE, 0, partsU, 0, partsV);
	else
		glEvalMesh2(GL_POINT, 0, partsU, 0, partsV);

	for (int i = 0; i < 4; i++) {
		glRasterPos3f(cntrlPoints[i][0], cntrlPoints[i][1],
				cntrlPoints[i][2] + 0.5);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '0' + i);
	}

}
void Patch::draw(textureSt *t) {
	draw();
}
