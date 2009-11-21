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
#include "Camera.h"

class ViewController
{
public:
	ViewController();
	
	void draw();
	// Used to assign players from game controller
	void setPlayer(int index, PlayerController* player);
	void mouseMove(float x, float y);
	//void moveCameraTo(float x, float y, float z);
	//void rotateCamera(float x, float y);
	void followPlayer(int player);
	void resetCamera();
	
	GLfloat levelCubes[20][3];
	
private:
	PlayerController* _players[kNumOfPlayers];
	Camera*	_camera;
};