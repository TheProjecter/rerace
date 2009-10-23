/*
 *  Racer.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <string>
#include <GLUT/GLUT.h>

using namespace std;

class Racer
{
public:
	Racer();
	Racer(GLfloat* startPostion);
	void draw();
	void move();
	void accelerate(GLfloat distance);
	void turn(GLfloat y);
	
	GLfloat* location();
	
private:
	GLfloat _position[3];
	GLfloat _speed;
	GLfloat _heading;
};
