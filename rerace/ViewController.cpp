/*
 *  ViewController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "ViewController.h"
#include "Primitives.h"
#include <Math.h>

#include <iostream>
GLuint rocklist;
GLuint textureBack;
GLuint skybox[6];

//Function to draw a cube, with 6 different textures on each edge
static void
drawTextureBox(GLfloat size, GLenum type, GLuint textures[6])
{
	// Create Faces of Cube
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
	
	// For each size, create corresponding square, and texture it
	for (i = 5; i >= 0; i--) {
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		glBegin(type);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0,0); glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0,1); glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1,1); glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1,0); glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	} 
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void 

// Function to call drawTextureBox function for simplicity
SolidTextureCube(GLdouble size, GLuint textures[6])
{
	drawTextureBox(size, GL_QUADS, textures);
}

// Default Viewcontroller constructor, creates asteroid field
// and Space Nebula Skybox
ViewController::ViewController()
{
	//load the Display list for the Asteroid Field
	rocklist = loadField();
	//Load each image of the SkyBox
	skybox[0] = LoadTextureRAW("S1.raw",1024/2, 1024/2, true, false);
	skybox[1] = LoadTextureRAW("S2.raw",1024/2, 1024/2, true, false);
	skybox[2] = LoadTextureRAW("S3.raw",1024/2, 1024/2, true, false);
	skybox[3] = LoadTextureRAW("S4.raw",1024/2, 1024/2, true, false);
	skybox[4] = LoadTextureRAW("S5.raw",1024/2, 1024/2, true, false);
	skybox[5] = LoadTextureRAW("S6.raw",1024/2, 1024/2, true, false);
	
	_camera = new Camera();
	_infoOverlay = new InformationOverlay();
}

// Default Viewcontroller desctructer
ViewController::~ViewController()
{
	delete _camera;
	delete _infoOverlay;
}

// Displays the skybox, always centered around the current camera position
// player can never reach skybox
void ViewController::renderSkybox(){
	float* cords = _players[0]->currentVehicleLocation();
	glPushMatrix();
	// translate skybox to current location
	glTranslatef(cords[0], cords[1], cords[2]);
	// Enable ambient lighting, to always show skybox, but not make it too harsh
	GLfloat mat_ambient[] = { 3.0, 3.0, 3.0, 3.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);	
	
	// Draw skybox
	SolidTextureCube(500, skybox);
	glPopMatrix();
	
}

// Draw the skybox, player, and Level - currently asteroids
void ViewController::draw()
{
	// Draw skybox
	renderSkybox();
	
	// Draw Players
	for(int i=0; i<kNumOfPlayers; i++)
		_players[i]->draw();
	
	// Write General Drawing Code (probably level and background)
	glCallList(rocklist);
}

// Reset the Camera
void ViewController::resetCamera()
{
	_camera->reset();
}

// Get current Player heading for camera
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