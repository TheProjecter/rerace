/*
 *  ViewController.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "ViewController.h"
#include "Primitives.h"
#include <Math.h>

#include <iostream>

ViewController::ViewController()
{
	for (int i=0; i<10; i++) {
		levelCubes[i][1] = (GLfloat)(rand()%6)-3;
		levelCubes[i][0] = -5.0-rand()%5;
		levelCubes[i][2] = (GLfloat)(rand()%6)-3;
	}
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;
	cameraPosition[2] = 0;	
	cameraAngle[0] = 0;
	cameraAngle[1] = 0;
}

void ViewController::draw()
{
	// Write General Drawing Code (probably level and background)
	for (int i=0; i<10; i++) {

		drawCube(levelCubes[i], .25);
	}
	// Draw Players
	for(int i=0; i<kNumOfPlayers; i++)
		_players[i]->draw();
	
}
void ViewController::resetCamera()
{
	int width =	glutGet( GLUT_WINDOW_WIDTH );
	int height = glutGet( GLUT_WINDOW_HEIGHT );
	
	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	cameraPosition[0] = 0;
	cameraPosition[1] = 0;
	cameraPosition[2] = 0;
	cameraAngle[0] = 0;
	cameraAngle[1] = 0;
	
	gluPerspective(90.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	
    glMatrixMode(GL_MODELVIEW);
}
void ViewController::moveCameraTo(float x, float y, float z)
{
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(cameraPosition[0]-x, cameraPosition[1]-y, cameraPosition[2]-z);

	glMatrixMode(GL_MODELVIEW);
	
	cameraPosition[0] = x;
	cameraPosition[1] = y;
	cameraPosition[2] = z;
}
void ViewController::rotateCamera(float x, float y)
{
	glMatrixMode(GL_PROJECTION);
	
	glTranslatef(cameraPosition[0], cameraPosition[1]-kCameraDistanceAbovePlayer, cameraPosition[2]-kCameraDistanceFromPlayer);
	
	glRotatef(cameraAngle[1]-y, 0, 1, 0);
	glRotatef(cameraAngle[0]-x, sinf((y+90)*M_PI/180), 0, cosf((y+90)*M_PI/180));
	
	glTranslatef(-cameraPosition[0], -cameraPosition[1]+kCameraDistanceAbovePlayer, -cameraPosition[2]+kCameraDistanceFromPlayer);
	
	glMatrixMode(GL_MODELVIEW);
	
	cameraAngle[0] = x;
	cameraAngle[1] = y;
}

// Used to assign players from game controller
void ViewController::setPlayer(int index, PlayerController* player)
{
	_players[index] = player;
}

void ViewController::mouseMove(float x, float y)
{
	/* 
	 * GameController's mouse move function will be called after so
	 * don't mess anything up perminently
	 */
}