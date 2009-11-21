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
	for (int i=0; i<20; i++) {
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