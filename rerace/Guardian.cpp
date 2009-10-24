/*
 *  Guardian.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Guardian.h"
#include "Primitives.h"
#include "constants.h"
#include <Math.h>
#include <iostream>

using namespace std;

GLfloat* Guardian::location()
{
	return _position;
}
GLfloat Guardian::headingX()
{
	return _headingX;
}
GLfloat Guardian::headingY()
{
	return _headingY;
}

Guardian::Guardian()
{
	_position = new GLfloat[3];
	_position[0]= 0;
	_position[1] = 0;
	_position[2] = 0;
	_speed = 0;
	_headingX = 0;
	_headingY = 0;
}

Guardian::Guardian(GLfloat* startPostion)
{
	_position = new GLfloat[3];
	_position[0]= startPostion[0];
	_position[1]= startPostion[1];
	_position[2]= startPostion[2];
	_speed = 0;
	_headingX = 0;
	_headingY = 0;
}

Guardian::~Guardian()
{
	delete _position;
}

void Guardian::move()
{
	_position[0] += _speed*sinf(_headingY*M_PI/180)*cosf(_headingX*M_PI/180);
	_position[1] -= _speed*sinf(_headingX*M_PI/180);
	_position[2] += _speed*cosf(_headingY*M_PI/180)*cosf(_headingX*M_PI/180);
	
	if(_speed>0)
		_speed-=kRacerFriction;
	else if(_speed<0)
		_speed+=kRacerFriction;
}

void Guardian::draw()
{
	move();
	glPushMatrix();
	
	glTranslatef(_position[0], _position[1], _position[2]);
	glRotatef(_headingY, 0, 1, 0);
	glRotatef(_headingX, 1, 0, 0);
	glTranslatef(-_position[0], -_position[1], -_position[2]);
	
	drawCube(_position, .1);
	
	glPopMatrix();
	
	/* Draw Perpedicular Line on x-z plane
	 * glColor3f(1.0, 0, 0);
	 * glBegin(GL_LINE_STRIP);
	 * glVertex3f(_position[0]-cos((_headingY)*M_PI/180)*10, _position[1], _position[2]+sin((_headingY)*M_PI/180)*10);
	 * glVertex3f(_position[0], _position[1], _position[2]);
	 * glEnd();
	 */
}

void Guardian::accelerate(GLfloat distance)
{
	_speed += distance;
}
void Guardian::turn(GLfloat x, GLfloat y)
{
	_headingX -= x;
	_headingY -= y;
}