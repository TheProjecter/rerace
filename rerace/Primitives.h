/*
 *  Primitives.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include <GLUT/GLUT.h>

void drawRect(GLfloat *va, GLfloat *vb, GLfloat *vc, GLfloat *vd);
void drawtriangle(GLfloat *va, GLfloat *vb, GLfloat *vc);
void drawCube(GLfloat *point, GLfloat size);
void drawTet(GLfloat *point, GLfloat size);