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

// Get current Player heading for camera and look towards that
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