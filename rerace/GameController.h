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
	void mainLoop(int cursorX, int cursorY);
	void keyboardFunction(unsigned char key, int x, int y);
	void mouseMove(float x, float y);
	
private:
	PlayerController* _players[kNumOfPlayers];
	ViewController* _viewController;
	
	int iterationCount;
};