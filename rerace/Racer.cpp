/*
 *  Racer.cpp
 *  rerace
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
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


// return the position
GLfloat* Racer::location()
{
	return _position;
}

// return the heading
GLfloat* Racer::heading()
{
	return _heading;
}

// return the up vector
GLfloat* Racer::up()
{
	return _up;
}

// Initialize racer to position 0,0,0 (calls init from drawing objects)
Racer::Racer()
{
	// set position
	_position[0] = 0;
	_position[1] = 0;
	_position[2] = 0;
	
	// set speed to 0
	_speed[0] = 0;
	_speed[1] = 0;
	_speed[2] = 0;
	speedMag = 0;
	
	// set looking forward
	_heading[0] = 0;
	_heading[1] = 0;
	_heading[2] = 1;
	
	// set up to be along y-axis
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
	
	// call initialization for drawing (from DrawingObjects.h)
	loadRacer();
}

// Initialize racer to position (calls init from drawing objects)
Racer::Racer(GLfloat* startPostion)
{
	// Note: if more contructors put defaults into shared init function
	
	// set position
	_position[0] = startPostion[0];
	_position[1] = startPostion[1];
	_position[2] = startPostion[2];
	
	// set speed to 0
	_speed[0] = 0;
	_speed[1] = 0;
	_speed[2] = 0;
	speedMag = 0;
	
	// set looking forward
	_heading[0] = 0;
	_heading[1] = 0;
	_heading[2] = 1;
	
	// set up to be along y-axis
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
}

// Move the racer based on current speed
void Racer::move()
{
	// Move racer
	_position[0] += _speed[0];
	_position[2] += _speed[2];
	
	// If magnitude is small set speed to 0
	if(speedMag<kRacerFriction & speedMag>-kRacerFriction)
	{
		_speed[0]=0;
		_speed[2]=0;
		speedMag=0;
	}
	
	// Apply friction if speed is not 0
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

// accelerate the racer in the direction of the current heading
void Racer::accelerate(GLfloat distance)
{
	_speed[0] += distance*_heading[0];
	_speed[2] += distance*_heading[2];
	speedMag +=  distance;
}


// turn the racer by a certain angle about the up axis
void Racer::turn(GLfloat y)
{
	// Horizontal Rotation
	rotateVectorAroundVector(_heading, _up, -y*M_PI/180);
}

// Draw the racer (calls draw from drawing objects)
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