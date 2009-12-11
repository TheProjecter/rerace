/*
 *  ViewController.h
 *  rerace
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/glut.h>

#include "constants.h"
#include "PlayerController.h"
#include "InformationOverlay.h"
#include "Camera.h"
#include "DrawingObjects.h"

void SolidTextureCube(GLdouble size, GLuint textures[6]);
static void drawTextureBox(GLfloat size, GLenum type, GLuint textures[6]);

class ViewController
{
public:
	ViewController();
	~ViewController();
	
	// Draw the skybox, player, and Level - currently asteroids
	void draw();
	// Used to assign players from game controller
	void setPlayer(int index, PlayerController* player);
	
	void mouseMove(float x, float y);
	// Displays the skybox, always centered around the current camera position
	// player can never reach skybox
	void renderSkybox();
	// Get current Player heading for camera and look towards that
	void followPlayer(int player);
	// Reset the Camera
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