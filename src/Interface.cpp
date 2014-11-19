/*
 * Interface.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: vania
 */

#include "Interface.h"

using namespace std;

Interface::Interface(ANFScene* scene) {
	this->scene = scene;

}

void Interface::initGUI() {
	GLUI_Panel *general = addPanel("Opcoes", 1);
	addColumnToPanel(general);
	GLUI_Panel *luzesPanel = addPanelToPanel(general, "Luzes", 1);

	map<string, lightSt*>::iterator it = scene->lights->lights.begin();
	int i = 0;
	for (it = scene->lights->lights.begin(); it != scene->lights->lights.end();
			it++) {

		string str = it->first;
		char * writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';

		if (it->second->enabled == true) {
			addCheckboxToPanel(luzesPanel, writable, NULL, i)->set_int_val(1);
		} else {
			addCheckboxToPanel(luzesPanel, writable, NULL, i)->set_int_val(0);
		}
		delete[] writable;
		scene->luzesId.push_back(it->second->id);
		i++;
	}

	addColumnToPanel(general);
	GLUI_Panel *camerasPanel = addPanelToPanel(general, "Camaras", 1);
	GLUI_RadioGroup *cameraList = addRadioGroupToPanel(camerasPanel,
			&scene->activeCam);

	std::map<std::string, cameraSt*>::iterator itc =
			scene->cameras->cameras.begin();
	i = 0;
	for (itc = scene->cameras->cameras.begin();
			itc != scene->cameras->cameras.end(); itc++) {

		string str = itc->first;
		char * writable = new char[str.size() + 1];
		copy(str.begin(), str.end(), writable);
		writable[str.size()] = '\0';

		if (itc == scene->cameras->curCam)
			addRadioButtonToGroup(cameraList, writable)->set_int_val(1);
		else
			addRadioButtonToGroup(cameraList, writable)->set_int_val(0);

		delete[] writable;
		scene->camerasId.push_back(itc->second->id);
		i++;
	}

	addRadioButtonToGroup(cameraList, "Default")->set_int_val(0);

	addColumnToPanel(general);
	GLUI_Panel *drawPanel = addPanelToPanel(general, "Draw Mode", 1);
	GLUI_RadioGroup *drawList = addRadioGroupToPanel(drawPanel,
			&scene->drawMode);
	addRadioButtonToGroup(drawList, "Fill");
	addRadioButtonToGroup(drawList, "Line");
	addRadioButtonToGroup(drawList, "Point");

	addColumnToPanel(general);
	GLUI_Panel *windPanel = addPanelToPanel(general, "Wind", 3);
	GLUI_Spinner *wind = addSpinnerToPanel(windPanel, "Wind", 2, &scene->wind,
			11);

	GLUI_Panel *animationPanel = addPanelToPanel(general, "Animation", 1);
	GLUI_Button *reset = addButtonToPanel(animationPanel, "Reset", 12);

}

void Interface::processGUI(GLUI_Control *ctrl) {

	if (ctrl->user_id >= 0)
		if (ctrl->user_id ==12) {
			scene->reset();

		} else if (ctrl->user_id != 11) {
			if (ctrl->get_int_val() == 1) {
				scene->activateLight(ctrl->user_id, true);
			} else {
				scene->activateLight(ctrl->user_id, false);
			}
		}

}

