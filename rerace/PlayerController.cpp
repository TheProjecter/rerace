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
	_usingRacer = true;
}

PlayerController::PlayerController(string newName, unsigned int playerId)
{	
	name = newName;
	_playerId = playerId;
	
	_racer = new Racer();
	_usingRacer = true;
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

void PlayerController::accelerate(GLfloat distance)
{
	if(_usingRacer)
		_racer->accelerate(distance);
	else
		_guardian->accelerate(distance);
}

void PlayerController::turn(GLfloat x, GLfloat y, GLfloat z)
{
	if(_usingRacer)
		_racer->turn(y);
	else
		_guardian->turn(x, y, z);
}