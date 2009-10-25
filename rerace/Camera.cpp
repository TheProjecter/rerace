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
	glTranslatef(position[0]-x, position[1]-y, position[2]-z);
	
	glMatrixMode(GL_MODELVIEW);
	
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

GLfloat dotProduct(GLfloat* v1, GLfloat x, GLfloat y, GLfloat z)
{
	return v1[0]*x + v1[1]*y + v1[2]*z;
}
GLfloat crossProductX(GLfloat a0, GLfloat a1, GLfloat a2, GLfloat* v2)
{
	return a1*v2[2]-a2*v2[1];
}
GLfloat crossProductY(GLfloat a0, GLfloat a1, GLfloat a2, GLfloat* v2)
{
	return a0*v2[2]-a2*v2[0];
}
GLfloat crossProductZ(GLfloat a0, GLfloat a1, GLfloat a2, GLfloat* v2)
{
	return a0*v2[1]-a1*v2[0];
}

void Camera::lookInDirection(GLfloat x, GLfloat y, GLfloat z)
{
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(position[0], position[1]-kCameraDistanceAbovePlayer, position[2]-kCameraDistanceFromPlayer);
	
	/*GLfloat angleOrig = atanf(direction[2]/direction[0])*180/M_PI;
	if(direction[0]<=0 & direction[2]<=0)
		angleOrig+=180;
	GLfloat angleNew = atanf(z/x)*180/M_PI;
	if(x<=0 & z<=0)
		angleNew+=180;
	cout<<z<<" / "<<x<<" = "<<angleNew<<endl;
	glRotatef(angleNew-angleOrig, 0, 1, 0);*/
	
	GLfloat newDirection[3] = {x, y, z};
	
	GLfloat xrot = acosf( dotProduct(direction, 1, 0, 0) );
	GLfloat yrot = acosf( dotProduct(direction, 0, 1, 0) );
	GLfloat zrot = acosf( dotProduct(direction, 0, 0, 1) );
	cout<<direction[0]<<" "<<direction[1]<<" "<<direction[2]<<endl;
	//cout<<xrot*180/M_PI<<" "<<yrot*180/M_PI<<" "<<zrot*180/M_PI<<endl;
	
	GLfloat xrotN = acosf( dotProduct(newDirection, 1, 0, 0) );
	GLfloat yrotN = acosf( dotProduct(newDirection, 0, 1, 0) );
	GLfloat zrotN = acosf( dotProduct(newDirection, 0, 0, 1) );
	
	glRotatef(-.5*(xrot-xrotN)*180/M_PI, crossProductX(1, 0, 0, newDirection), crossProductY(1, 0, 0, newDirection), crossProductZ(1, 0, 0, newDirection));
	glRotatef(-.5*(yrot-yrotN)*180/M_PI, crossProductX(0, 1, 0, newDirection), crossProductY(0, 1, 0, newDirection), crossProductZ(0, 1, 0, newDirection));
	glRotatef(-.5*(zrot-zrotN)*180/M_PI, crossProductX(0, 0, 1, newDirection), crossProductY(0, 0, 1, newDirection), crossProductZ(0, 0, 1, newDirection));
	
	glTranslatef(-position[0], -position[1]+kCameraDistanceAbovePlayer, -position[2]+kCameraDistanceFromPlayer);
	
	glMatrixMode(GL_MODELVIEW);
	
	direction[0] = x;
	direction[1] = y;
	direction[2] = z;
}