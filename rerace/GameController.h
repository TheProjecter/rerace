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
	void keyboardDownFunction(unsigned char key, int x, int y);
	void keyboardUpFunction(unsigned char key, int x, int y);
	void mouseMove(float x, float y);
	
	bool canTurnHorizontal;
	bool canTurnVertical;
	
private:
	PlayerController* _players[kNumOfPlayers];
	ViewController* _viewController;
	
	int iterationCount;
	GLfloat acceleration;
	GLfloat turningRadius;
};