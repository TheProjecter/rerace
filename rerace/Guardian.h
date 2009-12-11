/*
 *  Guardian.h
 *  rerace
 *	Object to control all aspects of a guardian. 
 *		- Calls draw functions from DrawingObjects.
 *		- Controls acceleration, speed, and position of guardian
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class Guardian 
{
public:
	// Initialize guardian to position 0,0,0 (calls init from drawing objects)
	Guardian();
	// Initialize guardian to position (calls init from drawing objects)
	Guardian(GLfloat* startPostion);
	~Guardian();
	
	// Draw the guardian (calls draw from DrawingObjects)
	void draw();
	// Move the guardian based on current speed
	void move();
	// accelerate the guardian in the direction of the current heading
	void accelerate(GLfloat distance);
	// turn the vector around the current right and up vectors
	void turn(GLfloat x, GLfloat y);
	
	// return the position
	GLfloat* location();
	// return the heading
	GLfloat* heading();
	// return the up vector
	GLfloat* up();
		
private:
	// Current physical position
	GLfloat* _position;
	// current speed
	GLfloat _speed;
	// direction the guardian is facing
	GLfloat _heading[3];
	// direction up from guardian
	GLfloat _up[3];
	// direction to the right from guardian
	GLfloat _right[3];
};