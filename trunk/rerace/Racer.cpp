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
	turnVector(_heading, 0, y);
	//GLfloat newX = cos(y*M_PI/180)*_heading[0] - sin(y*M_PI/180)*_heading[2];
	//GLfloat newZ = sin(y*M_PI/180)*_heading[0] + cos(y*M_PI/180)*_heading[2];
	
	//_heading[0] = newX;
	//_heading[2] = newZ;
	turnVector(_up, 0, y);
}

void Racer::draw()
{
	move();
	glPushMatrix();
	
	glTranslatef(_position[0], _position[1], _position[2]);
	
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	/*glVertex3f(0,0,0);
	 glVertex3f(10,0,0);
	 glVertex3f(0,0,0);
	 glVertex3f(0,10,0);*/
	glVertex3f(0, 0, 0);
	glVertex3f(-_heading[0],_heading[1],-_heading[2]);
	glEnd();
	
	if(_heading[2]<0)
		glRotatef(180+atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
	else
		glRotatef(atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
	
	drawCube(.1);
	
	glTranslatef(-_position[0], -_position[1], -_position[2]);
	
	glPopMatrix();
	
	/* Draw Perpedicular Line on x-z plane
	 * glColor3f(1.0, 0, 0);
	 * glBegin(GL_LINE_STRIP);
	 * glVertex3f(_position[0]-cos((_heading)*M_PI/180)*10, _position[1], _position[2]+sin((_heading)*M_PI/180)*10);
	 * glVertex3f(_position[0], _position[1], _position[2]);
	 * glEnd();
	 */
}