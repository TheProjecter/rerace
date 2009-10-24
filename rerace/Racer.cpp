/*
 *  Racer.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Racer.h"
#include "Primitives.h"
#include "constants.h"
#include <Math.h>

GLfloat* Racer::location()
{
	return _position;
}
GLfloat Racer::heading()
{
	return _heading;
}

Racer::Racer()
{
	_position = new GLfloat[3];
	_position[0] = 0;
	_position[1] = -kCameraDistanceAbovePlayer;
	_position[2] = -kCameraDistanceFromPlayer;
	_speed = 0;
	_heading = 0;
}

Racer::Racer(GLfloat* startPostion)
{
	_position = new GLfloat[3];
	_position[0] = startPostion[0];
	_position[1] = startPostion[1];
	_position[2] = startPostion[2];
	_heading = 0;
}

Racer::~Racer()
{
	delete _position;
}

void Racer::move()
{
	_position[0] += _speed*sin(_heading*M_PI/180);
	_position[2] += _speed*cos(_heading*M_PI/180);
	
	if(_speed>0)
		_speed-=kRacerFriction;
	else if(_speed<0)
		_speed+=kRacerFriction;
}

void Racer::accelerate(GLfloat distance)
{
	_speed += distance;
}

void Racer::turn(GLfloat y)
{
	_heading -= y;
}

void Racer::draw()
{
	move();
	glPushMatrix();
	
	glTranslatef(_position[0], _position[1], _position[2]);
	glRotatef(_heading, 0, 1, 0);
	glTranslatef(-_position[0], -_position[1], -_position[2]);
	
	
	drawCube(_position, .1);
	
	glPopMatrix();
	
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(_position[0]-cos((_heading)*M_PI/180)*10, _position[1], _position[2]+sin((_heading)*M_PI/180)*10);
	glVertex3f(_position[0], _position[1], _position[2]);
	glEnd();
}