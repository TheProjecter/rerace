/*
 *  Guardian.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class Guardian 
{
public:
	Guardian();
	Guardian(GLfloat* startPostion);
	void draw();
	GLfloat* location();
	void turn(GLfloat x, GLfloat y, GLfloat z);
	
	void accelerate(GLfloat distance);
		
private:
	GLfloat _position[3];
};