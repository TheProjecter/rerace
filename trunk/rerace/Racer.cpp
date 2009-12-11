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
#include "VectorMath.h"
#include <iostream>
#include "DrawingObjects.h"

using namespace std;



GLfloat* Racer::location()
{
	return _position;
}
GLfloat* Racer::heading()
{
	return _heading;
}
GLfloat* Racer::up()
{
	return _up;
}

Racer::Racer()
{
	_position[0] = 0;
	_position[1] = 0;
	_position[2] = 0;
	
	_speed[0] = 0;
	_speed[1] = 0;
	_speed[2] = 0;
	speedMag = 0;
	
	_heading[0] = 0;
	_heading[1] = 0;
	_heading[2] = 1;
	
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
	
	loadRacer();
}

Racer::Racer(GLfloat* startPostion)
{
	_position[0] = startPostion[0];
	_position[1] = startPostion[1];
	_position[2] = startPostion[2];
	
	_speed[0] = 0;
	_speed[1] = 0;
	_speed[2] = 0;
	speedMag = 0;
	
	_heading[0] = 0;
	_heading[1] = 0;
	_heading[2] = 0;
	
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
	
	loadRacer();
}

void Racer::move()
{
	_position[0] += _speed[0];
	_position[2] += _speed[2];
	
	// Apply friction
	if(speedMag<kRacerFriction & speedMag>-kRacerFriction)
	{
		_speed[0]=0;
		_speed[2]=0;
		speedMag=0;
	}
	
	if(speedMag!=0)
	{
		_speed[0]+=kRacerFriction*_speed[0]/speedMag;
		_speed[2]+=kRacerFriction*_speed[2]/speedMag;
	}
	
	if(speedMag>0)
		speedMag-=kRacerFriction;
	else
		speedMag+=kRacerFriction;
}

void Racer::accelerate(GLfloat distance)
{
	_speed[0] += distance*_heading[0];
	_speed[2] += distance*_heading[2];
	speedMag +=  distance;
}

void Racer::turn(GLfloat y)
{
	// Horizontal Rotation
	rotateVectorAroundVector(_heading, _up, -y*M_PI/180);
}

void Racer::draw()
{
	move();
	
	glPushMatrix();
	glTranslatef(_position[0], _position[1], _position[2]);
	
	if(_heading[2]<0)
		glRotatef(180+atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
	else
		glRotatef(atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
	glRotatef(180, 0, 1, 0);
	
	
	drawRacer(this);
	
	glPopMatrix();
}