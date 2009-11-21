/*
 *  Camera.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/24/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Camera.h"
#include <Math.h>
#include "VectorMath.h"
#include <iostream>
#include "constants.h"

using namespace std;

Camera::Camera()
{
	reset();
}

void Camera::reset()
{
	int width =	glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	
	glMatrixMode(GL_MODELVIEW);
	
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	direction[0] = 0;
	direction[1] = 0;
	direction[2] = 1;
}

void Camera::moveTo(GLfloat x, GLfloat y, GLfloat z)
{
	
	glMatrixMode(GL_PROJECTION);
	
	y+=kCameraDistanceAbovePlayer;
	z+=kCameraDistanceFromPlayer;
	glTranslatef(position[0]+x, position[1]+y, position[2]+z);
	
	glMatrixMode(GL_MODELVIEW);
	
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void Camera::lookInDirection(GLfloat* forward, GLfloat* up)
{
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	gluPerspective(90.0f,(GLfloat)glutGet( GLUT_WINDOW_WIDTH )/(GLfloat)glutGet( GLUT_WINDOW_HEIGHT ),0.1f,100.0f);
	
	glTranslatef(0, -kCameraDistanceAbovePlayer, -kCameraDistanceFromPlayer);
	
	/*GLfloat up[3], forward[3], right[3];
	forward[0]=x;
	forward[1]=y;
	forward[2]=z;
	
	GLfloat theta = atanf(x / z);
	right[0] = sinf(theta-M_PI/2);
	right[1] = 0;
	right[2] = cosf(theta-M_PI/2);
	
	cross(forward, right, up);*/
	/*if(acosf(dotProduct(forward, 0, 1, 0)>M_PI))
		yup = 1;
	else
		yup = -1;*/
	
	gluLookAt(position[0], position[1], position[2], position[0]-forward[0], position[1]+forward[1], position[2]-forward[2], 0, 1, 0);
	
	glTranslatef(0, kCameraDistanceAbovePlayer, kCameraDistanceFromPlayer);
	
	glMatrixMode(GL_MODELVIEW);
	
	direction[0] = forward[0];
	direction[1] = forward[1];
	direction[2] = forward[2];
}