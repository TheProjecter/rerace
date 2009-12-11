/*
 *  GameController.h
 *  rerace
 *
 *	Controls all game control and logic (serves as main loop for game)
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include "ViewController.h"

class GameController
{
public:
	// Initialize game controller with reference to view controller
	GameController(ViewController* viewController);
	// Timer function to be called for every frame (controls all gameplay)
	void mainLoop(int cursorX, int cursorY);
	
	// Functions to control players with keyboard
	void keyboardDownFunction(unsigned char key, int x, int y);
	void keyboardUpFunction(unsigned char key, int x, int y);
	
	// Function to control players with mouse
	void mouseMove(float x, float y);
	
	// For debugging purposes to restict turning to one direction
	bool canTurnHorizontal;
	bool canTurnVertical;
	
private:
	// List of players
	PlayerController* _players[kNumOfPlayers];
	// Reference to view controller
	ViewController* _viewController;
	
	// Variable to control if player accelerates or not 
	// (set to 0 when key is not being pressed)
	GLfloat acceleration;
	
	// Variable to control if player turns or not 
	// (set to 0 when key is not being pressed)
	GLfloat turningRadius;
};