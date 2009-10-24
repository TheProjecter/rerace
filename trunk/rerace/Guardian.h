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
	~Guardian();
	void draw();
	void move();
	void accelerate(GLfloat distance);
	void turn(GLfloat x, GLfloat y, GLfloat z);
	
	GLfloat* location();
	GLfloat headingX();
	GLfloat headingY();
		
private:
	GLfloat* _position;
	GLfloat _speed;
	GLfloat _headingX;
	GLfloat _headingY;
};