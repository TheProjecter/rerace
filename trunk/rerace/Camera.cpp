/*
 *  Camera.cpp
 *  rerace
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/24/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Camera.h"
#include <Math.h>
#include "VectorMath.h"
#include <iostream>
#include "constants.h"

#include "DrawingObjects.h"

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
	gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,0.1f,1000.0f);
	
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
	
	// Offset camera to be slightly behind and above player
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
	gluPerspective(90.0f,(GLfloat)glutGet( GLUT_WINDOW_WIDTH )/(GLfloat)glutGet( GLUT_WINDOW_HEIGHT ),0.1f,1000.0f);
	
	glTranslatef(0, -kCameraDistanceAbovePlayer, -kCameraDistanceFromPlayer);
	
	gluLookAt(position[0], position[1], position[2], position[0]-forward[0], position[1]-forward[1], position[2]-forward[2], up[0], up[1], up[2]);
	
	glTranslatef(0, kCameraDistanceAbovePlayer, kCameraDistanceFromPlayer);
	
	glMatrixMode(GL_MODELVIEW);
	
	direction[0] = forward[0];
	direction[1] = forward[1];
	direction[2] = forward[2];
}