/*
 *  Guardian.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Guardian.h"

GLfloat* Guardian::location()
{
	return _position;
}

Guardian::Guardian()
{
	
	_position[0]= -0.8;
	_position[1]= -0.8;
	_position[2]= -0.8;
}

Guardian::Guardian(GLfloat* startPostion)
{
	_position[0]= startPostion[0];
	_position[1]= startPostion[1];
	_position[2]= startPostion[2];
}

void Guardian::draw()
{
	//drawCube(_position, 1.6);
}

void Guardian::accelerate(GLfloat distance)
{
	
}
void Guardian::turn(GLfloat x, GLfloat y, GLfloat z)
{
	
}