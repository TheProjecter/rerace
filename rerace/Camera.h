/*
 *  Camera.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/24/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class Camera
{
public:
	Camera();
	void moveTo(GLfloat x, GLfloat y, GLfloat z);
	void lookInDirection(GLfloat* forward, GLfloat* up);
	void reset();
	
private:
	// Point where camera is located
	GLfloat position[3];
	// Unit Vector Representing Looking direction from Position
	GLfloat direction[3];
};