/*
 *  GameController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include <GLUT/glut.h>
#include <iostream>
#include "GameController.h"

using namespace std;

GameController::GameController(ViewController* newViewController)
{
	_viewController = newViewController;
	for(int i=0; i<kNumOfPlayers; i++)
	{
		_players[i] = new PlayerController();
		_viewController->setPlayer(i, _players[i]);
	}
	iterationCount = 0;
}

void GameController::mainLoop(int cursorX, int cursorY)
{	
	iterationCount++;
	
	GLfloat* player1Position = _players[0]->currentVehicleLocation();
	
	_viewController->moveCameraTo(player1Position[0], player1Position[1]+kCameraDistanceAbovePlayer, player1Position[2]+kCameraDistanceFromPlayer);
	_viewController->rotateCamera(_players[0]->currentVehicleHeadingX(), _players[0]->currentVehicleHeadingY() );
	
	int width =	glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	
	_viewController->mouseMove((float)(cursorX-width/2.0)/(float)width, (float)(cursorY-height/2.0)/(float)height);
	mouseMove((float)(cursorX-width/2.0)/(float)width, (float)(cursorY-height/2.0)/(float)height);

	// Reset the pointer to the center of the screen
	glutWarpPointer( width/2, height/2 );
}

void GameController::mouseMove(float x, float y)
{
	_players[0]->turn(y*kMouseSensitivity, x*kMouseSensitivity);
}

void GameController::keyboardFunction(unsigned char key, int x, int y)
{
	GLfloat acceleration = 0;
	if(key=='w')
	{
		acceleration = -kRacerForwardAcceleration;
	} else if (key=='s') {
		acceleration = kRacerForwardAcceleration;
	} else if (key=='e') {
		_players[0]->changeMode();
		_viewController->resetCamera();
	} else if (key=='`') {
		_viewController->resetCamera();
	}
	_players[0]->accelerate(acceleration);
}