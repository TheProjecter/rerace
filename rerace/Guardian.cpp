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
#include "VectorMath.h"
#include <iostream>
#include "DrawingObjects.h"

using namespace std;

GLfloat* Guardian::location()
{
	return _position;
}
GLfloat* Guardian::heading()
{
	return _heading;
}
GLfloat* Guardian::up()
{
	return _up;
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
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
	_right[0] = 1;
	_right[1] = 0;
	_right[2] = 0;
	
	loadGuardian();
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
	_up[0] = 0;
	_up[1] = 1;
	_up[2] = 0;
	_right[0] = 0;
	_right[1] = -1;
	_right[2] = 0;
	
	loadGuardian();
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
	
	//glTranslatef(_position[0], _position[1], _position[2]);
	//glRotatef(_heading[0], 1, 0, 0);
	//glRotatef(_heading[1], 0, 1, 0);
	//glRotatef(_headingY, 0, cosf((_headingX)*M_PI/180), sinf((_headingX)*M_PI/180));
	
	/*glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(-_heading[0],_heading[1],-_heading[2]);
	glVertex3f(0, 0, 0);
	glVertex3f(-_up[0],_up[1],-_up[2]);
	glEnd();*/
	
	/*if(_heading[2]<0)
	{
		//glRotatef(180+atanf(_heading[1]/_heading[2])*180/M_PI, 1, 0, 0);
		glRotatef(180+atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
		
	} else
	{
		//glRotatef(atanf(_heading[1]/_heading[2])*180/M_PI, 1, 0, 0);
		glRotatef(atanf(_heading[0]/_heading[2])*180/M_PI, 0, 1, 0);
	}*/
	
	glLoadIdentity();
	
	glTranslatef(_position[0], _position[1], _position[2]);
	
	gluLookAt(0, 0, 0,
			  //-_position[0], -_position[1], -_position[2],
			  -_heading[0],-_heading[1],-_heading[2],
			  //_position[0]+_up[0],-_position[1]+_up[1],-_position[2]+_up[2]);
			  //-_position[0]+_heading[0], -_position[1]-_heading[1], -_position[2]-_heading[2],
			  //0, 1, 0);
			 -_up[0], -_up[1], -_up[2]);
	
	/*glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glEnd();*/
	
	//drawCube(.1);
	drawGuardian(this);
	
	glPopMatrix();
	
	/* Draw orthogonal line to the right */
	/*glColor3f(1.0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-cos((_heading[1])*M_PI/180)*10, 0, sin((_heading[1])*M_PI/180)*10);
	glVertex3f(0, 0, 0);
	glEnd();
	
	/* Draw orthogonal line upwards
	glColor3f(0, 0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(sinf(_heading[1]*M_PI/180)*cosf((_heading[0]-90)*M_PI/180)*10, sinf((_heading[0]-90)*M_PI/180)*10, cosf(_heading[1]*M_PI/180)*cosf((_heading[1]-90)*M_PI/180)*10);
	glVertex3f(0,0,0);
	glEnd();*/
	
	// Draw Heading
	glColor3f(0, 1.0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(_position[0], _position[1], _position[2]);
	glVertex3f(_position[0]-_heading[0]/4,_position[1]-_heading[1]/4,_position[2]-_heading[2]/4);
	
	// Draw Up
	glColor3f(1.0, 0, 0);
	glVertex3f(_position[0], _position[1], _position[2]);
	glVertex3f(_position[0]+_up[0]/4,_position[1]+_up[1]/4,_position[2]+_up[2]/4);
	
	// Draw Right
	glColor3f(0, 0, 1.0);
	glVertex3f(_position[0], _position[1], _position[2]);
	glVertex3f(_position[0]+_right[0]/4,_position[1]+_right[1]/4,_position[2]+_right[2]/4);
	glEnd();
	
}

void Guardian::accelerate(GLfloat distance)
{
	_speed += distance;
}
void Guardian::turn(GLfloat x, GLfloat y)
{
	// Horizontal Rotation
	rotateVectorAroundVector(_heading, _up, -y*M_PI/180);
	rotateVectorAroundVector(_right, _up, -y*M_PI/180);
	
	// Vertical Rotation
	rotateVectorAroundVector(_heading, _right, -x*M_PI/180);
	rotateVectorAroundVector(_up, _right, -x*M_PI/180);
	
	//cout<<x<<" "<<y<<endl;
	
	//turnVector(_heading, x, y);
	//turnVector(_up, x, y);
}