#include "ANFScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"
#include <unistd.h>
#include <iostream>
#include <math.h>

#include "CGFappearance.h"
void ANFScene::setDisplayList(map<string, NodeSt>::iterator node,
		map<string, appearanceSt*>::iterator appearanceId, bool force) {


	bool useText = true;
	map<string, appearanceSt*>::iterator next = appearanceId;
	if (node->second.usingDL && !force) {
		node->second.dl = glGenLists(this->dlcount);
		this->dlcount++;
		glNewList(node->second.dl, GL_COMPILE);
		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glMultMatrixf(node->second.matrix);
		if (node->second.appearanceId->second->id != "inherit") {

			node->second.appearanceId->second->appe->apply();
			if (node->second.appearanceId->second->hasText) {
				next = node->second.appearanceId;
				useText = true;
			} else {
				useText = false;
			}
		} else {

			appearanceId->second->appe->apply();
			if (appearanceId->second->hasText) {
				useText = true;
			} else {
				useText = false;
			}
		}
		for (int i = 0; i < node->second.primitives.size(); i++) {
			if (useText) {

				node->second.primitives[i]->draw(
						next->second->textureref->second);
			} else
				node->second.primitives[i]->draw();
		}
		for (int i = 0; i < node->second.descendents.size(); i++) {
			setDisplayList(node->second.descendents[i], next, true);
		}
		glPopMatrix();
		glEndList();
	} else if (force) {
		glPushMatrix();
		glMultMatrixf(node->second.matrix);
		if (node->second.appearanceId->second->id != "inherit") {

			node->second.appearanceId->second->appe->apply();
			if (node->second.appearanceId->second->hasText) {
				next = node->second.appearanceId;
				useText = true;
			} else {
				useText = false;
			}
		} else {

			appearanceId->second->appe->apply();
			if (appearanceId->second->hasText) {
				useText = true;
			} else {
				useText = false;
			}
		}
		for (int i = 0; i < node->second.primitives.size(); i++) {
			if (useText) {

				node->second.primitives[i]->draw(
						next->second->textureref->second);
			} else
				node->second.primitives[i]->draw();
		}
		for (int i = 0; i < node->second.descendents.size(); i++) {
			setDisplayList(node->second.descendents[i], next, true);
		}
	glPopMatrix();
	} else {

		for (int i = 0; i < node->second.descendents.size(); i++) {
			setDisplayList(node->second.descendents[i], next, false);
		}
	}

}

ANFScene::ANFScene(char *filename) {
// Read XML from file

	doc = new TiXmlDocument(filename);
	bool loadOkay = doc->LoadFile();
	if (!loadOkay) {
		printf("Could not load file '%s'. Error='%s'. Exiting.\n", filename,
				doc->ErrorDesc());
		exit(1);
	}
	anfElement = doc->FirstChildElement("anf");
	if (anfElement == NULL) {
		printf("Main anf block element not found! Exiting!\n");
		exit(1);
	}
	globalElements = anfElement->FirstChildElement("globals");
	if (globalElements == NULL) {
		printf("Couldn't find globals element\n");
		exit(1);
	}
	cameraElements = anfElement->FirstChildElement("cameras");
	if (cameraElements == NULL) {
		printf("Couldn't find camera element\n");
		exit(1);
	}
	lightElements = anfElement->FirstChildElement("lights");
	if (lightElements == NULL) {
		printf("Couldn't find light element\n");
		exit(1);
	}
	textureElements = anfElement->FirstChildElement("textures");
	if (textureElements == NULL) {
		printf("Couldn't find texture element\n");
		exit(1);
	}
	appearanceElements = anfElement->FirstChildElement("appearances");
	if (appearanceElements == NULL) {
		printf("Couldn't find appearance element\n");
		exit(1);
	}
	graphElements = anfElement->FirstChildElement("graph");
	if (graphElements == NULL) {
		printf("Couldn't find graph element\n");
		exit(1);
	}

}

void ANFScene::init() {

//---------------------------------------------------------------------------------
//Globals
	printf("start reading anf\n");
	draw = new drawingSt();
	TiXmlElement* drawingElement = globalElements->FirstChildElement("drawing");
	if (drawingElement == NULL) {
		printf("drawing null\n");
		exit(-1);
	}
	draw->mode = drawingElement->Attribute("mode");

	draw->shading = drawingElement->Attribute("shading");
	float back[4];
	sscanf((char*) drawingElement->Attribute("background"), "%f %f %f %f",
			&back[0], &back[1], &back[2], &back[3]);
	for (int i = 0; i < 4; i++) {
		draw->background.push_back(back[i]);
	}

	printf("read drawing\n");
	culling = new cullingSt();
	TiXmlElement* cullingElement = globalElements->FirstChildElement("culling");
	if (cullingElement == NULL) {
		printf("culling null\n");
		exit(-1);
	}
	culling->face = cullingElement->Attribute("face");
	culling->order = cullingElement->Attribute("order");

	printf("read culling\n");

	lighting = new lightingSt();
	TiXmlElement* lightingElement = globalElements->FirstChildElement(
			"lighting");
	if (lightingElement == NULL) {
		printf("lighting null\n");
		exit(-1);
	}
	lightingElement->QueryBoolAttribute("doublesided", &lighting->doublesided);
	lightingElement->QueryBoolAttribute("local", &lighting->local);
	lightingElement->QueryBoolAttribute("enabled", &lighting->enabled);
	float ambient[4];
	sscanf((char*) lightingElement->Attribute("ambient"), "%f %f %f %f",
			&ambient[0], &ambient[1], &ambient[2], &ambient[3]);

	for (int i = 0; i < 4; i++) {
		lighting->ambient.push_back(ambient[i]);
	}

	printf("read lighting\n");
	printf("read globals\n");
/////////////////////////////////////////////////////////////
	float globalAmbientLight[4];
	for (int i = 0; i < 4; i++)
		globalAmbientLight[i] = lighting->ambient[i];
	if (lighting->enabled)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
	if (lighting->doublesided)
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);
	if (lighting->local)
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	else
		glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientLight);
	if (draw->shading == "flat")
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);
	glClearColor(draw->background[0], draw->background[1], draw->background[2],
			draw->background[3]);
//Globals culling
	glEnable(GL_CULL_FACE);
	if (culling->face == "none")
		glDisable(GL_CULL_FACE);
	else if (culling->face == "front")
		glCullFace(GL_FRONT);
	else if (culling->face == "back")
		glCullFace(GL_BACK);
	else
		glCullFace(GL_FRONT_AND_BACK);
	if (culling->order == "cw")
		glFrontFace(GL_CW);
	else
		glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);

/////////////////////////////////////////////////////////7

	cameras = new cameraMp();

	for (TiXmlElement* cam = cameraElements->FirstChildElement("ortho");
			cam != NULL; cam = cam->NextSiblingElement("ortho")) {
		printf("reading ortho cams\n");
		string id = cam->Attribute("id");
		string direction = cam->Attribute("direction");
		float near;
		cam->QueryFloatAttribute("near", &near);
		float far;
		cam->QueryFloatAttribute("far", &far);
		float left;
		cam->QueryFloatAttribute("left", &left);
		float right;
		cam->QueryFloatAttribute("right", &right);
		float top;
		cam->QueryFloatAttribute("top", &top);
		float bottom;
		cam->QueryFloatAttribute("bottom", &bottom);
		printf("add cam id : %s\n", id.c_str());
		cameras->addOrthoCam(id, direction, near, far, left, right, top,
				bottom);
	}
	printf("read ortho cams\n");
	for (TiXmlElement* cam = cameraElements->FirstChildElement("perspective");
			cam != NULL; cam = cam->NextSiblingElement("perspective")) {
		printf("reading persp cam\n");
		string id = cam->Attribute("id");
		float near;
		cam->QueryFloatAttribute("near", &near);
		float far;
		cam->QueryFloatAttribute("far", &far);
		float angle;
		cam->QueryFloatAttribute("angle", &angle);
		float pos[3];
		sscanf((char*) cam->Attribute("pos"), "%f %f %f", &pos[0], &pos[1],
				&pos[2]);
		float target[3];
		sscanf((char*) cam->Attribute("target"), "%f %f %f", &target[0],
				&target[1], &target[2]);
		vector<float> vpos, vtarget;
		for (int i = 0; i < 3; i++) {
			vpos.push_back(pos[i]);
			vtarget.push_back(target[i]);
		}
		cameras->addPrespCam(id, near, far, angle, vpos, vtarget);

	}

	printf("read presp cams\n");
	char* inicam = (char*) cameraElements->Attribute("initial");
	printf("%s\n", inicam);
	cameras->curCam = cameras->getCamera(inicam);
	cameras->curCam->second->print();
	int lightArray[8] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4,
	GL_LIGHT5, GL_LIGHT6, GL_LIGHT7 };
	lights = new lightMp();
	int i = 0;
	for (TiXmlElement* light = lightElements->FirstChildElement("light");
			light != NULL; light = light->NextSiblingElement("light")) {
		printf("reading a light\n");
		string id = light->Attribute("id");
		string type = light->Attribute("type");
		bool enabled;
		light->QueryBoolAttribute("enabled", &enabled);
		bool marker;
		light->QueryBoolAttribute("marker", &marker);
		float pos[4];
		sscanf((char*) light->Attribute("pos"), "%f %f %f", &pos[0], &pos[1],
				&pos[2]);
		pos[3] = 1;
		float ambienta[4];
		float diffuse[4];
		float specular[4];
		for (TiXmlElement* fil = light->FirstChildElement("component");
				fil != NULL; fil = fil->NextSiblingElement("component")) {
			char* tipo = ((char*) fil->Attribute("type"));
			printf("component child do tipo:%s\n", tipo);
			if (strcmp(tipo, "ambient") == 0) {
				sscanf((char*) fil->Attribute("value"), "%f %f %f %f",
						&ambienta[0], &ambienta[1], &ambienta[2], &ambienta[3]);
			} else if (strcmp(tipo, "diffuse") == 0) {
				sscanf((char*) fil->Attribute("value"), "%f %f %f %f",
						&diffuse[0], &diffuse[1], &diffuse[2], &diffuse[3]);
			} else {
				sscanf((char*) fil->Attribute("value"), "%f %f %f %f",
						&specular[0], &specular[1], &specular[2], &specular[3]);
			}
		}

		CGFlight* cglight;
		float dir[3];
		if (type == "spot") {
			printf("creating spot\n");
			float target[3];
			sscanf((char*) light->Attribute("target"), "%f %f %f", &target[0],
					&target[1], &target[2]);

			float angle;
			light->QueryFloatAttribute("angle", &angle);
			float exponent;
			light->QueryFloatAttribute("exponent", &exponent);
			for (int j = 0; j < 3; j++) {
				target[j] = pos[j] - target[j];
			}

			float unit = sqrt(
					target[0] * target[0] + target[1] * target[1]
							+ target[2] * target[2]);
			for (int j = 0; j < 3; j++) {
				target[j] = target[j] / unit;
			}
			printf("angle : %f \n exponent: %f \n dir1 : %f\n", angle, exponent,
					dir[0]);

			cglight = new CGFlight(lightArray[i], pos, target);
			cglight->setAngle(angle);
		} else {
			cglight = new CGFlight(lightArray[i], pos);
			cglight->setAngle(180);
		}
		for (int k = 0; k < 3; k++)
			printf("dir%d: %f\n", k, dir[k]);

		printf("pos : %f %f %f %f\n", pos[0], pos[1], pos[2], pos[3]);
		// 	cglight = new CGFlight(lightArray[i], pos);
		printf("ambient: %f %f %f %f\n", ambienta[0], ambienta[1], ambienta[2],
				ambienta[3]);
		printf("specular: %f %f %f %f\n", specular[0], specular[1], specular[2],
				specular[3]);
		printf("diffuse: %f %f %f %f\n", diffuse[0], diffuse[1], diffuse[2],
				diffuse[3]);
		cglight->setAmbient(ambienta);
		cglight->setSpecular(specular);
		cglight->setDiffuse(diffuse);
		cglight->enable();

		printf("diffuse : %f %f %f\n", diffuse[0], diffuse[1], diffuse[2]);

		lights->addLight(id, cglight, marker, enabled);
		i++;
	}
	printf("finished reading lights\n");

	textures = new textureMp();
	for (TiXmlElement* text = textureElements->FirstChildElement("texture");
			text != NULL; text = text->NextSiblingElement("texture")) {
		string id = text->Attribute("id");
		string file = text->Attribute("file");
		float texlenght_s;
		text->QueryFloatAttribute("texlenght_s", &texlenght_s);
		float texlenght_t;
		text->QueryFloatAttribute("texlenght_t", &texlenght_t);
		textures->addTexture(id, file, texlenght_s, texlenght_t);
		printf("added texture %s with file %s\n", id.c_str(), file.c_str());

	}
	printf("finished reading textures\n");

	appearances = new appearanceMp();
	float empty[3] = { 0, 0, 0 };
	appearances->addAppearance("inherit",
			new CGFappearance(empty, empty, empty, 1),
			textures->getTexture("nada"), false);
	for (TiXmlElement* appe = appearanceElements->FirstChildElement(
			"appearance"); appe != NULL;
			appe = appe->NextSiblingElement("appearance")) {
		printf("reading an appearance\n");
		string id = appe->Attribute("id");
		string textureRef = appe->Attribute("textureref");
		printf("cenas\n");
		float shininess;
		appe->QueryFloatAttribute("shininess", &shininess);
		float ambient[3];
		float diffuse[3];
		float specular[3];
		for (TiXmlElement* fil = appe->FirstChildElement("component");
				fil != NULL; fil = fil->NextSiblingElement("component")) {
			printf("child component\n");
			if (strcmp(fil->Attribute("type"), "ambient") == 0) {
				sscanf((char*) fil->Attribute("value"), "%f %f %f %f",
						&ambient[0], &ambient[1], &ambient[2], &ambient[3]);
			} else if (strcmp(fil->Attribute("type"), "diffuse") == 0) {
				sscanf((char*) fil->Attribute("value"), "%f %f %f %f",
						&diffuse[0], &diffuse[1], &diffuse[2], &diffuse[3]);
			} else {
				sscanf((char*) fil->Attribute("value"), "%f %f %f %f",
						&specular[0], &specular[1], &specular[2], &specular[3]);
			}
		}

		CGFappearance* temp = new CGFappearance(ambient, diffuse, specular,
				shininess);
		bool hasText = false;
		if (textureRef != "") {
			printf("%s\n", textureRef.c_str());
			hasText = true;
			temp->setTexture(textures->getTexture(textureRef)->second->file);
		}
		appearances->addAppearance(id, temp, textures->getTexture(textureRef),
				hasText);

	}
	printf("finished reading appearance\n");

	graph = new GraphMp();
	string rootId = graphElements->Attribute("rootid");
	graph->rootId = graph->getNode(rootId);

	for (TiXmlElement* node = graphElements->FirstChildElement("node");
			node != NULL; node = node->NextSiblingElement("node")) {
		printf("start reading a node\n");
		string id = node->Attribute("id");
		bool useDL=false;
		node->QueryBoolAttribute("displaylist",&useDL);

		TiXmlElement* transforms = node->FirstChildElement("transforms");
		printf("start reading a transform\n");
		if (transforms != NULL) {
			glLoadIdentity();
			for (TiXmlElement* transf = transforms->FirstChildElement(
					"transform"); transf != NULL;
					transf = transf->NextSiblingElement("transform")) {
				string type = transf->Attribute("type");
				if (type == "translate") {
					float to[3];
					sscanf((char*) transf->Attribute("to"), "%f %f %f", &to[0],
							&to[1], &to[2]);
					glTranslatef(to[0], to[1], to[2]);

				} else if (type == "rotate") {
					string axis = transf->Attribute("axis");
					float angle;
					transf->QueryFloatAttribute("angle", &angle);
					glRotatef(angle, axis == "x", axis == "y", axis == "z");

				} else {
					float factor[3];
					sscanf((char*) transf->Attribute("factor"), "%f %f %f",
							&factor[0], &factor[1], &factor[2]);
					glScalef(factor[0], factor[1], factor[2]);
				}
			}
		}
		float matrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
		printf("finished reading transforms\n");
		vector<PrimSt*> primitives = vector<PrimSt*>();
		TiXmlElement* primitiveElements = node->FirstChildElement("primitives");
		if (primitiveElements != NULL) {
			for (TiXmlElement* rectangle = primitiveElements->FirstChildElement(
					"rectangle"); rectangle != NULL;
					rectangle = rectangle->NextSiblingElement("rectangle")) {
				float pt1[2], pt2[2];
				sscanf((char*) rectangle->Attribute("xy1"), "%f %f", &pt1[0],
						&pt1[1]);
				sscanf((char*) rectangle->Attribute("xy2"), "%f %f", &pt2[0],
						&pt2[1]);
				vector<float> vpt1, vpt2;
				for (int i = 0; i < 2; i++) {
					vpt1.push_back(pt1[i]);
					vpt2.push_back(pt2[i]);
				}
				primitives.push_back(new RectangleSt(vpt1, vpt2));

			}
			for (TiXmlElement* triangle = primitiveElements->FirstChildElement(
					"triangle"); triangle != NULL;
					triangle = triangle->NextSiblingElement("triangle")) {
				float pt1[3], pt2[3], pt3[3];
				sscanf((char*) triangle->Attribute("xyz1"), "%f %f %f", &pt1[0],
						&pt1[1], &pt1[2]);
				sscanf((char*) triangle->Attribute("xyz2"), "%f %f %f", &pt2[0],
						&pt2[1], &pt2[2]);
				sscanf((char*) triangle->Attribute("xyz3"), "%f %f %f", &pt3[0],
						&pt3[1], &pt3[2]);
				vector<float> vpt1, vpt2, vpt3;
				for (int i = 0; i < 3; i++) {
					vpt1.push_back(pt1[i]);
					vpt2.push_back(pt2[i]);
					vpt3.push_back(pt3[i]);
				}
				primitives.push_back(new TriangleSt(vpt1, vpt1, vpt3));

			}
			for (TiXmlElement* cylinder = primitiveElements->FirstChildElement(
					"cylinder"); cylinder != NULL;
					cylinder = cylinder->NextSiblingElement("cylinder")) {
				float base, top, height;
				int slices, stacks;
				cylinder->QueryFloatAttribute("base", &base);
				cylinder->QueryFloatAttribute("top", &top);
				cylinder->QueryFloatAttribute("height", &height);
				cylinder->QueryIntAttribute("slices", &slices);
				cylinder->QueryIntAttribute("stacks", &stacks);
				primitives.push_back(
						new CylinderSt(base, top, height, slices, stacks));

			}
			for (TiXmlElement* sphere = primitiveElements->FirstChildElement(
					"sphere"); sphere != NULL;
					sphere = sphere->NextSiblingElement("sphere")) {
				float radius;
				int slices, stacks;
				sphere->QueryFloatAttribute("radius", &radius);
				sphere->QueryIntAttribute("slices", &slices);
				sphere->QueryIntAttribute("stacks", &stacks);
				primitives.push_back(new SphereSt(radius, slices, stacks));

			}
			for (TiXmlElement* plane = primitiveElements->FirstChildElement(
					"plane"); plane != NULL;
					plane = plane->NextSiblingElement("plane")) {
				int parts;
				plane->QueryIntAttribute("parts",&parts);
				primitives.push_back(new Plane(parts));

			}
			for (TiXmlElement* torus = primitiveElements->FirstChildElement(
					"torus"); torus != NULL;
					torus = torus->NextSiblingElement("torus")) {
				float inner, outer;
				int slices, loops;
				torus->QueryFloatAttribute("inner", &inner);
				torus->QueryFloatAttribute("outer", &outer);
				torus->QueryIntAttribute("slices", &slices);
				torus->QueryIntAttribute("loops", &loops);
				primitives.push_back(new TorusSt(inner, outer, slices, loops));

			}
			printf("finished reading primitives\n");
			vector<map<string, NodeSt>::iterator> descendants = vector<
					map<string, NodeSt>::iterator>();
			TiXmlElement* descendantElements = node->FirstChildElement(
					"descendants");
			if (descendantElements != NULL) {
				for (TiXmlElement* desc = descendantElements->FirstChildElement(
						"noderef"); desc != NULL;
						desc = desc->NextSiblingElement("noderef")) {
					string id = desc->Attribute("id");

					descendants.push_back(graph->getNode(id));

				}
			}
			map<string, appearanceSt*>::iterator appearance;
			TiXmlElement* appearanceref = node->FirstChildElement(
					"appearanceref");
			string idapp = appearanceref->Attribute("id");
			appearance = appearances->getAppearance(idapp);
			graph->addNode(id, appearance, descendants, primitives,useDL);
			for (int i = 0; i < 16; i++)
				graph->nodes[id].matrix[i] = matrix[i];
			printf("finished reading node\n");
		}
	}
	printf("finished reading graph\n");

	printf("finished reading anf\n");

/////////////////////////////////////////////////////////////////////////////////////

//displaylsits
	setDisplayList(graph->rootId,
			appearances->appearances.end(), false);


}

void ANFScene::display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (drawMode == 0)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else if (drawMode == 1)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	if (this->activeCam == cameras->cameras.size())
		CGFscene::activeCamera->applyView();
	else {
		cameras->getCamera((char*) camerasId[activeCam].c_str())->second->apply();
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	CGFapplication::activeApp->forceRefresh();
	std::map<std::string, lightSt*>::iterator it = lights->lights.begin();

	for (it = lights->lights.begin(); it != lights->lights.end(); it++) {
		CGFlight *cglight = it->second->light;
		cglight->draw();

	}
	axis.draw();

	graph->draw(appearances->appearances.end());

	glutSwapBuffers();
}
void ANFScene::activateLight(int id, bool enable) {
	lights->getLight(luzesId[id])->enabled = enable;
	if (enable)
		lights->getLight(luzesId[id])->light->enable();
	else
		lights->getLight(luzesId[id])->light->disable();

}

ANFScene::~ANFScene() {
}


