/*
 *  ViewController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "ViewController.h"
#include "Primitives.h"
#include <Math.h>

#include <iostream>
GLuint rocklist;
GLuint textureBack;

static void
drawBox2(GLfloat size, GLenum type)
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	};
	GLfloat v[8][3];
	GLint i;
	
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
	
	for (i = 5; i >= 0; i--) {
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0,0); glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0,1); glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1,1); glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1,0); glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	} 
}

void 
glutSolidCube2(GLdouble size)
{
	drawBox2(size, GL_QUADS);
}


ViewController::ViewController()
{
	
	rocklist = loadField();
	textureBack = LoadTextureRAW("back.raw",1024, 1024, true, false);
	_camera = new Camera();
	_infoOverlay = new InformationOverlay();
}
ViewController::~ViewController()
{
	delete _camera;
	delete _infoOverlay;
}

void ViewController::renderSkybox(){
	float* cords = _players[0]->currentVehicleLocation();
	glPushMatrix();
	glTranslatef(cords[0], cords[1], cords[2]);
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 0.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	
	glBindTexture(GL_TEXTURE_2D, textureBack);
	glutSolidCube2(250);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glPopMatrix();
	
}

void ViewController::draw()
{
	renderSkybox();
	
	// Draw Players
	for(int i=0; i<kNumOfPlayers; i++)
		_players[i]->draw();
	
	// Write General Drawing Code (probably level and background)
	glCallList(rocklist);
}
void ViewController::resetCamera()
{
	_camera->reset();
}
void ViewController::followPlayer(int player)
{
	GLfloat* playerPosition = _players[player]->currentVehicleLocation();
	
	_camera->moveTo(playerPosition[0], playerPosition[1], playerPosition[2]);
	_camera->lookInDirection(_players[player]->currentVehicleHeading(),
							 _players[player]->currentVehicleUp());
}

// Used to assign players from game controller
void ViewController::setPlayer(int index, PlayerController* player)
{
	_players[index] = player;
}

void ViewController::mouseMove(float x, float y)
{
	/* 
	 * GameController's mouse move function will be called after so
	 * don't mess anything up perminently
	 */
}