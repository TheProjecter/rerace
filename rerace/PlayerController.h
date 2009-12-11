/*
 *  PlayerController.h
 *  rerace
 *
 *	Acts as generic player object as a proxy and calls the 
 *	appropriate functions on either guardian or racer
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Racer.h"
#include "Guardian.h"

#include <GLUT/GLUT.h>
#include <string>

using namespace std;

class PlayerController
{
public:
	// Initialize player and create guardian and racer
	PlayerController();
	// Initialize player with name and playerId and create guardian and racer
	PlayerController(string name, unsigned int playerId);
	
	// Return the position of the ship that is currently being controlled
	GLfloat* currentVehicleLocation();
	// Return the heading of the ship that is currently being controlled
	GLfloat* currentVehicleHeading();
	// Return the up vector of the ship that is currently being controlled
	GLfloat* currentVehicleUp();
	// Return bool for which ship is being controlled
	bool controllingRacer();
	// Call draw for both ships
	void draw();
	
	// accelerate the current ship
	void accelerate(GLfloat distance);
	// turn the current ship
	void turn(GLfloat x, GLfloat y, bool mouse);
	// switch between ships
	void changeMode();

private:
	unsigned int _playerId;
	string name;
	
	bool _usingRacer;
	Racer* _racer;
	Guardian* _guardian;
};