/*
 *  InformationOverlay.h
 *  rerace
 *
 *  Created by Andrew Wagner on 11/21/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

class InformationOverlay
{
public:
	InformationOverlay();
	void draw(unsigned int time, int position, int lap);
	
private:
	GLuint numTexture;
};

