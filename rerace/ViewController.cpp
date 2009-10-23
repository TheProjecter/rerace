/*
 *  ViewController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "ViewController.h"

void ViewController::draw()
{
	// Write General Drawing Code (probably level and background)
	
	
	// Draw Players
	for(int i=0; i<kNumOfPlayers; i++)
		_players[i]->draw();
	
}

// Used to assign players from game controller
void ViewController::setPlayer(int index, PlayerController* player)
{
	_players[index] = player;
}