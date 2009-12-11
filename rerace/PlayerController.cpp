/*
 *  PlayerController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "PlayerController.h"

// Initialize player and create guardian and racer
PlayerController::PlayerController()
{
	name = "undefined";
	_playerId = 0;
	
	_racer = new Racer();
	_guardian = new Guardian();
	_usingRacer = true;
}

// Initialize player with name and playerId and create guardian and racer
PlayerController::PlayerController(string newName, unsigned int playerId)
{	
	name = newName;
	_playerId = playerId;
	
	_racer = new Racer();
	_guardian = new Guardian();
	_usingRacer = true;
}

// Return bool for which ship is being controlled
bool PlayerController::controllingRacer()
{
	return _usingRacer;
}

// switch between ships
void PlayerController::changeMode()
{
	_usingRacer = !_usingRacer;
}

// Call draw for both ships
void PlayerController::draw()
{
	_racer->draw();
	_guardian->draw();
}

// Return the position of the ship that is currently being controlled
GLfloat* PlayerController::currentVehicleLocation()
{
	if(_usingRacer)
		return _racer->location();
	return _guardian->location();
}

// Return the heading of the ship that is currently being controlled
GLfloat* PlayerController::currentVehicleHeading()
{
	if(_usingRacer)
		return _racer->heading();
	return _guardian->heading();
}

// Return the up vector of the ship that is currently being controlled
GLfloat* PlayerController::currentVehicleUp()
{
	if(_usingRacer)
		return _racer->up();
	return _guardian->up();
}

// accelerate the current ship
void PlayerController::accelerate(GLfloat distance)
{
	if(_usingRacer)
		_racer->accelerate(distance);
	else
		_guardian->accelerate(distance);
}

// turn the current ship
void PlayerController::turn(GLfloat x, GLfloat y, bool mouse)
{
	if(_usingRacer & !mouse)
		_racer->turn(y);
	else if(!_usingRacer & mouse)
		_guardian->turn(x, y);
}