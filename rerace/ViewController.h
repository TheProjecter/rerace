/*
 *  ViewController.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/glut.h>

#include "constants.h"
#include "PlayerController.h"

class ViewController
{
public:
	void draw();
	// Used to assign players from game controller
	void setPlayer(int index, PlayerController* player);
	
private:
	PlayerController* _players[kNumOfPlayers];
};