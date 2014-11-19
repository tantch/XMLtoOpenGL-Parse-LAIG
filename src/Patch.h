
#ifndef SRC_PATCH_H_
#define SRC_PATCH_H_
#include "dataStructs.h"

class Patch:public PrimSt{
public:
	Patch(int order,int partsU,int PartsV,string compute,vector< vector< float > > cntrlPoints);
	virtual ~Patch();
	void draw();
	void draw(textureSt *t);


	int order,partsU,partsV;
	string compute;
	vector< float > textPoints, cntrlPoints;
};

#endif /* SRC_PATCH_H_ */
