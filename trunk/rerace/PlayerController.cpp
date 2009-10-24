/*
 *  PlayerController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "PlayerController.h"

PlayerController::PlayerController()
{	
	name = "undefined";
	_playerId = 0;
	
	_racer = new Racer();
	_guardian = new Guardian();
	_usingRacer = true;
}

bool PlayerController::controllingRacer()
{
	return _usingRacer;
}

PlayerController::PlayerController(string newName, unsigned int playerId)
{	
	name = newName;
	_playerId = playerId;
	
	_racer = new Racer();
	_guardian = new Guardian();
	_usingRacer = true;
}

void PlayerController::changeMode()
{
	_usingRacer = !_usingRacer;
}

void PlayerController::draw()
{
	_racer->draw();
	_guardian->draw();
}

GLfloat* PlayerController::currentVehicleLocation()
{
	if(_usingRacer)
		return _racer->location();
	return _guardian->location();
}

GLfloat PlayerController::currentVehicleHeadingX()
{
	if(_usingRacer)
		return 0;
	return _guardian->headingX();
}
GLfloat PlayerController::currentVehicleHeadingY()
{
	if(_usingRacer)
		return _racer->heading();
	return _guardian->headingY();
}

void PlayerController::accelerate(GLfloat distance)
{
	if(_usingRacer)
		_racer->accelerate(distance);
	else
		_guardian->accelerate(distance);
}

void PlayerController::turn(GLfloat x, GLfloat y)
{
	if(_usingRacer)
		_racer->turn(y);
	else
		_guardian->turn(x, y);
}