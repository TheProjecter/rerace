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
}

PlayerController::PlayerController(string newName, unsigned int playerId)
{	
	name = newName;
	_playerId = playerId;
	
	_racer = new Racer();
}

void PlayerController::draw()
{
	_racer->draw();
	_guardian->draw();
}