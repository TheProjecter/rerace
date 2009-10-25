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
	acceleration = 0;
	turningRadius = 0;
}

void GameController::mainLoop(int cursorX, int cursorY)
{	
	_players[0]->accelerate(acceleration);
	_players[0]->turn(0, turningRadius, false);
	
	iterationCount++;
	
	_viewController->followPlayer(0);
	
	int width =	glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	
	_viewController->mouseMove((float)(cursorX-width/2.0)/(float)width, (float)(cursorY-height/2.0)/(float)height);
	mouseMove((float)(cursorX-width/2.0)/(float)width, (float)(cursorY-height/2.0)/(float)height);

	// Reset the pointer to the center of the screen
	glutWarpPointer( width/2, height/2 );
}

void GameController::mouseMove(float x, float y)
{
	_players[0]->turn(y*kMouseSensitivity, x*kMouseSensitivity, true);
}

void GameController::keyboardDownFunction(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w':
			acceleration = -kRacerForwardAcceleration;
			break;
		case 's':
			acceleration = kRacerForwardAcceleration;
			break;
		case 'a':
			turningRadius = -kRacerTurnRadius;
			break;
		case 'd':
			turningRadius = kRacerTurnRadius;
			break;
		default:
			break;
	}
}
void GameController::keyboardUpFunction(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w':
			acceleration = 0;
			break;
		case 's':
			acceleration = 0;
			break;
		case 'a':
			turningRadius = 0;
			break;
		case 'd':
			turningRadius = 0;
			break;
		case 'e':
			_players[0]->changeMode();
			_viewController->resetCamera();
			break;
		case '`':
			_viewController->resetCamera();
			break;
		default:
			break;
	}
}