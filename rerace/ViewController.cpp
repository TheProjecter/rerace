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

ViewController::ViewController()
{
	for (int i=0; i<10; i++) {
		levelCubes[i][0] = (GLfloat)(rand()%6)-3;
		levelCubes[i][1] = (GLfloat)(rand()%6)-3;
		levelCubes[i][2] = -5.0-rand()%5;
	}
	
	_camera = new Camera();
}

void ViewController::draw()
{
	// Write General Drawing Code (probably level and background)
	for (int i=0; i<10; i++) {

		drawCube(levelCubes[i], .25);
	}
	// Draw Players
	for(int i=0; i<kNumOfPlayers; i++)
		_players[i]->draw();
	
}
void ViewController::resetCamera()
{
	_camera->reset();
}
void ViewController::followPlayer(int player)
{
	GLfloat* playerPosition = _players[player]->currentVehicleLocation();
	GLfloat* playerHeading = _players[player]->currentVehicleHeading();
	
	_camera->moveTo(playerPosition[0], playerPosition[1], playerPosition[2]);
	_camera->lookInDirection(playerHeading[0], playerHeading[1], playerHeading[2]);
}
/*void ViewController::moveCameraTo(float x, float y, float z)
{
	_camera->moveTo(x, y, z);
}*/
/*
void ViewController::rotateCamera(float x, float y)
{
	_camera->lookInDirection(x, y);
	/*GLfloat oldPosition[3] = {cameraPosition[0],cameraPosition[1],cameraPosition[2]};
	resetCamera();
	moveCameraTo(oldPosition[0], oldPosition[1], oldPosition[2]);
	
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(cameraPosition[0], cameraPosition[1]-kCameraDistanceAbovePlayer, cameraPosition[2]-kCameraDistanceFromPlayer);
	glRotatef(cameraAngle[1]-y,0,1,0);
	glRotatef(cameraAngle[0]-x,1,0,0);
	
	//glRotatef(cameraAngle[1]-y, -cosf((cameraAngle[0]+90)*M_PI/180), sinf((cameraAngle[0]+90)*M_PI/180), 0);
	//glRotatef(cameraAngle[0]-x, sinf((y+90)*M_PI/180), 0, cosf((y+90)*M_PI/180));
	
	glTranslatef(-cameraPosition[0], -cameraPosition[1]+kCameraDistanceAbovePlayer, -cameraPosition[2]+kCameraDistanceFromPlayer);
	
	glMatrixMode(GL_MODELVIEW);
	
	cameraAngle[0] = x;
	cameraAngle[1] = y;
}*/

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