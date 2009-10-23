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
		
private:
	GLfloat _position[3];
};