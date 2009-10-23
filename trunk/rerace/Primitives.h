/*
 *  Primitives.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/22/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */
#include <GLUT/GLUT.h>

void drawRect(GLfloat *va, GLfloat *vb, GLfloat *vc, GLfloat *vd)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	glVertex3fv(vd);
}

void drawCube(GLfloat *point, GLfloat size)
{
	glBegin(GL_QUADS);
	
	GLfloat *a = point;
	GLfloat b[3] = {point[0] ,point[1], point[2]+size};
	GLfloat c[3] = {point[0]+size,point[1], point[2]+size};
	GLfloat d[3] = {point[0]+size ,point[1], point[2]};
	
	GLfloat e[3] = {point[0] ,point[1]+size, point[2]};
	GLfloat f[3] = {point[0] ,point[1]+size, point[2]+size};
	GLfloat g[3] = {point[0]+size ,point[1]+size, point[2]+size};
	GLfloat h[3] = {point[0]+size ,point[1]+size, point[2]};
	
	GLfloat colors[6][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}};
	
	// Top
    glColor3fv(colors[0]);
    drawRect(a, b, c, d);
	
	// Left
    glColor3fv(colors[1]);
    drawRect(a, b, f, e);
	
	// Right
    glColor3fv(colors[2]);
    drawRect(d, c, g, h);
	
	// Bottom
    glColor3fv(colors[3]);
    drawRect(e, f, g, h);
	
	// Back
    glColor3fv(colors[4]);
    drawRect(a, d, h, e);
	
	// Front
    glColor3fv(colors[5]);
    drawRect(b, c, g, f);
	
	glEnd();
}