/*
 *  Racer.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class Racer
{
public:
	Racer();
	Racer(GLfloat* startPostion);
	~Racer();
	void draw();
	void move();
	void accelerate(GLfloat distance);
	void turn(GLfloat y);
	
	GLfloat* location();
	GLfloat heading();
	
private:
	GLfloat* _position;
	GLfloat _speed;
	GLfloat _heading;
};
