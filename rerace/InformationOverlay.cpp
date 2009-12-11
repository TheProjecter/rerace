/*
 *  InformationOverlay.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 11/21/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "InformationOverlay.h"
#include "PNGTexture.h"
#include <iostream>
#include <string>

InformationOverlay::InformationOverlay() {
	std::string file = "numbers.png";
	setupGLTexture(file.c_str(), 64, numTexture);
}

void InformationOverlay::draw(unsigned int time, int position, int lap)
{
	
	// Draw Background
	
	glBegin(GL_POLYGON);
	glColor4f(1, 0, 0, .8);
	glVertex3f(-1,	-.8,	-1);
	glVertex3f(-1,	-1,		-1);
	glVertex3f(1,	-1,		-1);
	glVertex3f(1,	-.8,	-1);
	
	glEnd();
	
	// Draw Time
	//std::cout<<(int)time/1000<<std::endl;
	
	glBindTexture(GL_TEXTURE_2D, numTexture);
	
	glBegin(GL_POLYGON);
	//glColor4f(1,1,1,1);
	
	glTexCoord2f(0,.1);
	glVertex3f(-.95,	-.8,	-1);
	glTexCoord2f(0,0);
	glVertex3f(-.95,	-.95,	-1);
	glTexCoord2f(.1,0);
	glVertex3f(-.8,		-.95,	-1);
	glTexCoord2f(.1,.1);
	glVertex3f(-.8,		-.8,	-1);
	
	glEnd();
	
	
	
}

