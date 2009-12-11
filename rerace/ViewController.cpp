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
	srand(time(0));
	for (int i=0; i<100; i++) {
		levelCubes[i][0] = ((GLfloat)(rand()%10000)-5000.0)/1000.0;
		levelCubes[i][1] = ((GLfloat)(rand()%10000)-5000.0)/1000.0;
		levelCubes[i][2] = ((GLfloat)(rand()%10000)-5000.0)/1000.0;
	}
	
	_camera = new Camera();
	_infoOverlay = new InformationOverlay();
}
ViewController::~ViewController()
{
	delete _camera;
	delete _infoOverlay;
}

void ViewController::draw()
{
	// Draw Players
	for(int i=0; i<kNumOfPlayers; i++)
		_players[i]->draw();
	
	// Write General Drawing Code (probably level and background)
	for (int i=0; i<10; i++) {
		glTranslatef(levelCubes[i][0], levelCubes[i][1], levelCubes[i][2]);
		glutSolidTeapot(.25);
		//drawCube(.25);
		glTranslatef(-levelCubes[i][0], -levelCubes[i][1], -levelCubes[i][2]);
	}

	// Reset View and Draw Overlay (in 2D)
	/*glMatrixMode(GL_PROJECTION);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	_infoOverlay->draw(raceTime, position, lap);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);*/
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