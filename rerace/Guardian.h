/*
 *  Guardian.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class Guardian 
{
public:
	Guardian();
	Guardian(GLfloat* startPostion);
	~Guardian();
	void draw();
	void move();
	void accelerate(GLfloat distance);
	void turn(GLfloat x, GLfloat y);
	
	GLfloat* location();
	GLfloat* heading();
		
private:
	GLfloat* _position;
	GLfloat _speed;
	GLfloat _heading[3];
};