/*
 *  GameController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include <GLUT/glut.h>
#include "GameController.h"

void GameController::mainLoop()
{
	/*glRotatef(5, 0, 1, 0);
	glRotatef(5, 0, 0, 1);
	glRotatef(5, 1, 0, 0);*/
}

GameController::GameController(ViewController* newViewController)
{
	_viewController = newViewController;
	for(int i=0; i<kNumOfPlayers; i++)
	{
		_players[i] = new PlayerController();
		_viewController->setPlayer(i, _players[i]);
	}
}