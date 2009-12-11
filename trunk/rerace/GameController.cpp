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

// Initialize game controller with reference to view controller
GameController::GameController(ViewController* newViewController)
{
	_viewController = newViewController;
	// Create all of the players
	for(int i=0; i<kNumOfPlayers; i++)
	{
		_players[i] = new PlayerController();
		// Share player references with view contoller (for drawing)
		_viewController->setPlayer(i, _players[i]);
	}
	acceleration = 0;
	turningRadius = 0;
}

// Timer function to be called for every frame (controls all gameplay)
void GameController::mainLoop(int cursorX, int cursorY)
{	
	// Update game variables
	_viewController->raceTime+=kGameSpeed;
	_viewController->position=1;
	_viewController->lap=1;
	
	// Accelerate and turn the player being controlled
	_players[0]->accelerate(acceleration);
	_players[0]->turn(0, turningRadius, false);
	
	// Have camera follow player
	_viewController->followPlayer(0);
	
	// Send mouse movements to camera and player for turning
	int width =	glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	_viewController->mouseMove((float)(cursorX-width/2.0)/(float)width, (float)(cursorY-height/2.0)/(float)height);
	mouseMove((float)(cursorX-width/2.0)/(float)width, (float)(cursorY-height/2.0)/(float)height);

	// Reset the pointer to the center of the screen
	glutWarpPointer( width/2, height/2 );
}

// Send mouse movements to player
void GameController::mouseMove(float x, float y)
{
	float turnYRadius = y*kMouseSensitivity;
	float turnXRadius = x*kMouseSensitivity;
	
	// If in debugging mode only allow turning for pressed button
	if(kFlyingDebuggingMode & !canTurnVertical)
		turnXRadius = 0;
	if(kFlyingDebuggingMode & !canTurnHorizontal)
		turnYRadius = 0;
	
	_players[0]->turn(turnYRadius, turnXRadius, true);
}

// Function to control players with keyboard
void GameController::keyboardDownFunction(unsigned char key, int x, int y)
{
	switch (key) {
		case 'w': // move racer forward
			acceleration = -kRacerForwardAcceleration;
			break;
		case 's': // move racer back
			acceleration = kRacerForwardAcceleration;
			break;
		case 'a': // turn racer left
			turningRadius = -kRacerTurnRadius;
			break;
		case 'd': // turn racer right
			turningRadius = kRacerTurnRadius;
			break;
		case '1': // allow vertical rotation in debugging mode
			canTurnVertical = true;
			break;
		case '2': // allow vertical rotation
			canTurnHorizontal = true;
			break;
		default:
			break;
	}
}
// Functions to control players with keyboard
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
		case 'e': // Change control between racer and guardian (and reset the camera to follow new ship)
			_players[0]->changeMode();
			_viewController->resetCamera();
			break;
		case '`': // reset camera for debugging
			_viewController->resetCamera();
			break;
		case '1':
			canTurnVertical = false;
			break;
		case '2':
			canTurnHorizontal = false;
			break;
		default:
			break;
	}
}