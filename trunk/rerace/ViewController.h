/*
 *  ViewController.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/glut.h>

#include "constants.h"
#include "PlayerController.h"
#include "InformationOverlay.h"
#include "Camera.h"
#include "DrawingObjects.h"

void glutSolidCube2(GLdouble size, GLuint textures[6]);
static void drawBox2(GLfloat size, GLenum type, GLuint textures[6]);

class ViewController
{
public:
	ViewController();
	~ViewController();
	
	void draw();
	// Used to assign players from game controller
	void setPlayer(int index, PlayerController* player);
	void mouseMove(float x, float y);
	void renderSkybox();
	//void moveCameraTo(float x, float y, float z);
	//void rotateCamera(float x, float y);
	void followPlayer(int player);
	void resetCamera();
	
	GLfloat levelCubes[100][3];
	
	unsigned int raceTime;
	int position;
	int lap;
	
private:
	PlayerController* _players[kNumOfPlayers];
	Camera*	_camera;
	InformationOverlay* _infoOverlay;
};