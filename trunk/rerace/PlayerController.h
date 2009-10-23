/*
 *  PlayerController.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
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
	PlayerController();
	PlayerController(string name, unsigned int playerId);
	
	GLfloat* currentVehicleLocation();
	void draw();
	
	void accelerate(GLfloat distance);
	void turn(GLfloat x, GLfloat y, GLfloat z);

private:
	unsigned int _playerId;
	string name;
	
	bool _usingRacer;
	Racer* _racer;
	Guardian* _guardian;
};