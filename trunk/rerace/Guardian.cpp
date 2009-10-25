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
GLfloat* Guardian::heading()
{
	return _heading;
}

Guardian::Guardian()
{
	_position = new GLfloat[3];
	_position[0]= 0;
	_position[1] = 0;
	_position[2] = 0;
	_speed = 0;
	_heading[0] = 0;
	_heading[1] = 0;
	_heading[2] = 1;
}

Guardian::Guardian(GLfloat* startPostion)
{
	_position = new GLfloat[3];
	_position[0]= startPostion[0];
	_position[1]= startPostion[1];
	_position[2]= startPostion[2];
	_speed = 0;
	_heading[0] = 0;
	_heading[1] = 0;
	_heading[2] = 0;
}

Guardian::~Guardian()
{
	delete _position;
}

void Guardian::move()
{
	_position[0] += _speed*_heading[0];
	_position[1] -= _speed*_heading[1];
	_position[2] += _speed*_heading[2];
	/*_position[0] += _speed*sinf(_heading[1]*M_PI/180)*cosf(_heading[0]*M_PI/180);
	_position[1] -= _speed*sinf(_heading[0]*M_PI/180);
	_position[2] += _speed*cosf(_heading[1]*M_PI/180)*cosf(_heading[0]*M_PI/180);*/
	
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
	//glRotatef(_heading[0], 1, 0, 0);
	//glRotatef(_heading[1], 0, 1, 0);
	//glRotatef(_headingY, 0, cosf((_headingX)*M_PI/180), sinf((_headingX)*M_PI/180));
	
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
	{
		//glRotatef(180+atanf(_heading[1]/_heading[2])*180/M_PI, 1, 0, 0);
		glRotatef(180+atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
		
	} else
	{
		//glRotatef(atanf(_heading[1]/_heading[2])*180/M_PI, 1, 0, 0);
		glRotatef(atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
		
	}
	
	glTranslatef(-_position[0], -_position[1], -_position[2]);
	
	drawCube(_position, .1);
	
	glPopMatrix();
	
	/* Draw orthogonal line to the right
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(_position[0]-cos((_headingY)*M_PI/180)*10, _position[1], _position[2]+sin((_headingY)*M_PI/180)*10);
	glVertex3f(_position[0], _position[1], _position[2]);
	glEnd();
	
	/* Draw orthogonal line upwards
	glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(_position[0]+sinf(_headingY*M_PI/180)*cosf((_headingX-90)*M_PI/180)*10, _position[1]-sinf((_headingX-90)*M_PI/180)*10, _position[2]+cosf(_headingY*M_PI/180)*cosf((_headingX-90)*M_PI/180)*10);
	glVertex3f(_position[0], _position[1], _position[2]);
	glEnd();
	*/
}

void Guardian::accelerate(GLfloat distance)
{
	_speed += distance;
}
void Guardian::turn(GLfloat x, GLfloat y)
{
	GLfloat newX = cos(y*M_PI/180)*_heading[0] - sin(y*M_PI/180)*_heading[2];
	GLfloat newZ = sin(y*M_PI/180)*_heading[0] + cos(y*M_PI/180)*_heading[2];
	
	_heading[0] = newX;
	_heading[2] = newZ;
	
	/*GLfloat newY = cos(x*M_PI/180)*_heading[1] - sin(x*M_PI/180)*_heading[2];
	newZ = sin(x*M_PI/180)*_heading[1] + cos(x*M_PI/180)*_heading[2];
	
	_heading[1] = newY;
	_heading[2] = newZ;*/
}