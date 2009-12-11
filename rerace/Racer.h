/*
 *  Racer.h
 *  rerace
 *	Object to control all aspects of a racer. 
 *		- Calls draw functions from DrawingObjects.
 *		- Controls acceleration, speed, and position of racer
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class Racer
{
public:
	// Initialize racer to position 0,0,0 (calls init from drawing objects)
	Racer();
	// Initialize racer to position (calls init from drawing objects)
	Racer(GLfloat* startPostion);
	~Racer();
	
	// Draw the racer (calls draw from DrawingObjects)
	void draw();
	// Move the racer based on current speed
	void move();
	// accelerate the racer in the direction of the current heading
	void accelerate(GLfloat distance);
	// turn the racer by a certain angle about the up axis
	void turn(GLfloat y);
	
	// return the position
	GLfloat* location();
	// return the heading
	GLfloat* heading();
	// return the up vector
	GLfloat* up();
	
private:	
	// Current physical position
	GLfloat _position[3];
	// current speed
	GLfloat _speed[3];
	// magnitude of the speed for use with friction
	GLfloat speedMag;
	// the direction the racer if facing
	GLfloat _heading[3];
	// the direction up from the racer
	GLfloat _up[3];
};
