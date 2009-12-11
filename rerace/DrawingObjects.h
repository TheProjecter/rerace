/*
 *  DrawingObjects.h
 *  rerace
 *
 *  Created by Keith Thompson on 12/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

GLuint LoadTextureRAW( const char * filename, int width, int height, int wrap, bool transparent );

// Initialization functions
void loadRacer();
void loadGuardian();
void loadRock();

// Drawing functions
void drawRacer(void* racer);
void drawGuardian(void* guardian);
void drawRock();
GLuint loadField();