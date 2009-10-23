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

ViewController::ViewController()
{
	for (int i=0; i<10; i++) {
		levelCubes[i][0] = (GLfloat)(rand()%6)-3;
		levelCubes[i][1] = (GLfloat)(rand()%6)-3;
		levelCubes[i][2] = -5.0-rand()%5;
	}
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;
	cameraPosition[2] = 0;	
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
void ViewController::moveCameraTo(float x, float y, float z)
{
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(cameraPosition[0]-x, cameraPosition[1]-y, cameraPosition[2]-z);

	glMatrixMode(GL_MODELVIEW);
	
	cameraPosition[0] = x;
	cameraPosition[1] = y;
	cameraPosition[2] = z;
}

// Used to assign players from game controller
void ViewController::setPlayer(int index, PlayerController* player)
{
	_players[index] = player;
}

void ViewController::mouseMove(float x, float y)
{
	/* 
	 * GameControllers mouse move function will be called after so
	 * don't mess anything up perminently
	 */
	
	glMatrixMode(GL_PROJECTION);
	
	GLfloat* player1Position = _players[0]->currentVehicleLocation();
	
	glTranslatef(player1Position[0], player1Position[1], player1Position[2]);
	glRotatef(x*kMouseSensitivity, 0, 1, 0);
	//glRotatef(y*50.0, 1, 0, 0);
	glTranslatef(-player1Position[0], -player1Position[1], -player1Position[2]);
	
	glMatrixMode(GL_MODELVIEW);
}