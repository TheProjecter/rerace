/*
 *  GameController.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include "ViewController.h"

class GameController
{
public:
	GameController(ViewController* viewController);
	void mainLoop();
	
private:
	PlayerController* _players[kNumOfPlayers];
	ViewController* _viewController;
};