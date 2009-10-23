/*
 *  Racer.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Racer.h"
#import "Primitives.h"

Racer::Racer()
{
	
	_position[0]= -0.8;
	_position[1]= -0.8;
	_position[2]= -0.8;
}

Racer::Racer(GLfloat* startPostion)
{
	_position[0]= startPostion[0];
	_position[1]= startPostion[1];
	_position[2]= startPostion[2];
}

void Racer::draw()
{
	drawCube(_position, 1.6);
}