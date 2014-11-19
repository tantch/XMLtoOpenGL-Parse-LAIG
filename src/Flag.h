
#ifndef SRC_FLAG_H_
#define SRC_FLAG_H_
#include "Plane.h"
#include "dataStructs.h"
#include "ShaderFlag.h"
class Flag:public PrimSt {
public:
	Flag(string texture);
	virtual ~Flag();
	Plane* plane;
	void draw();
	void draw(textureSt *t);

	ShaderFlag* shader;
};

#endif /* SRC_FLAG_H_ */
