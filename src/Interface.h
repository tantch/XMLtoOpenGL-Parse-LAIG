/*
 * Interface.h
 *
 *  Created on: Oct 19, 2014
 *      Author: vania
 */

#include "CGFinterface.h"
#include "ANFScene.h"
#include "dataStructs.h"
#include <string>
#include <vector>

#ifndef SRC_INTERFACE_H_
#define SRC_INTERFACE_H_

class Interface: public CGFinterface {
private:
	ANFScene* scene;

public:

	Interface(ANFScene* scene);
	void initGUI();
	void processGUI(GLUI_Control *control);
};

#endif /* SRC_INTERFACE_H_ */
