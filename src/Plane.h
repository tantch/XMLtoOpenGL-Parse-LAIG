
#ifndef SRC_PLANE_H_
#define SRC_PLANE_H_
#include "dataStructs.h"
class Plane:public PrimSt{
public:
	Plane(int div);
	virtual ~Plane();
	void draw();
	void draw(textureSt *t);
	int divs;
};

#endif /* SRC_PLANE_H_ */
