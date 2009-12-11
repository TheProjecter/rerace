/*
 *  Primitives.h
 *  rerace
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include <GLUT/GLUT.h>
#include <string>

using namespace std;

void drawRect(GLfloat *va, GLfloat *vb, GLfloat *vc, GLfloat *vd);
void drawtriangle(GLfloat *va, GLfloat *vb, GLfloat *vc);
void drawCube(GLfloat size);
void drawTet(GLfloat size);
void drawmodel(string model);