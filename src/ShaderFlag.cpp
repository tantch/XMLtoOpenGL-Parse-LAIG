#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include "ShaderFlag.h"

ShaderFlag::ShaderFlag() {
	baseTexture = new CGFtexture("tex/leaf.jpg");
	init("flag.vert", "flag.frag");
	CGFshader::bind();

	startTime=0.0;
	time=0.0;
	timeLoc = glGetUniformLocation(id(), "time");
	angle = 0.0;

	angleLoc = glGetUniformLocation(id(), "angle");

	baseTextLoc = glGetUniformLocation(id(), "baseTexture");

	glUniform1i(baseTextLoc, 0);

	CGFshader::unbind();

}
ShaderFlag::~ShaderFlag() {

}

void ShaderFlag::bind() {
	CGFshader::bind();

	// update uniforms
	glUniform1f(angleLoc, angle);
	glUniform1f(timeLoc, time);
	// make sure the correct texture unit is active
	glActiveTexture(GL_TEXTURE0);

	// apply/activate the texture you want, so that it is bound to GL_TEXTURE0
	baseTexture->apply();

}
void ShaderFlag::unbind() {
	CGFshader::unbind();
}
void ShaderFlag::update(unsigned long t) {
	if (startTime = 0) {
		startTime = t;
	} else {
		time = t - startTime;
	}

}
