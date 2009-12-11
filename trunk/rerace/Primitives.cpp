/*
 *  Primitives.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/23/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "Primitives.h"
#include "glm.h"

void drawmodel(string model)
{
	GLMmodel* pmodel;
	pmodel = glmReadOBJ(model.c_str());
	if(!pmodel) return;
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    glmScale(pmodel, .1);
	glmDraw(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}


void drawRect(GLfloat *va, GLfloat *vb, GLfloat *vc, GLfloat *vd)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	glVertex3fv(vd);
}

void drawTriangle(GLfloat *va, GLfloat *vb, GLfloat *vc, GLfloat *vd)
{	
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	
}

void drawCube(GLfloat size)
{	
	glBegin(GL_QUADS);
	GLfloat x = - size/2.0;
	GLfloat y = - size/2.0;
	GLfloat z = - size/2.0;
	
	GLfloat a[3] = {x, y, z};
	GLfloat b[3] = {x ,y, z+size};
	GLfloat c[3] = {x+size,y, z+size};
	GLfloat d[3] = {x+size ,y, z};
	
	GLfloat e[3] = {x ,y+size, z};
	GLfloat f[3] = {x ,y+size, z+size};
	GLfloat g[3] = {x+size ,y+size, z+size};
	GLfloat h[3] = {x+size ,y+size, z};
	
	GLfloat colors[6][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}};
	
	// Bottom
    glColor3fv(colors[0]);
    drawRect(a, b, c, d);
	
	// Left
    glColor3fv(colors[1]);
    drawRect(a, b, f, e);
	
	// Right
    glColor3fv(colors[2]);
    drawRect(d, c, g, h);
	
	// Top
    glColor3fv(colors[3]);
    drawRect(e, f, g, h);
	
	// Front
    glColor3fv(colors[4]);
    drawRect(a, d, h, e);
	
	// Back
    glColor3fv(colors[5]);
    drawRect(b, c, g, f);
	
	glEnd();
}

void drawTet(GLfloat size)
{	
	/*glBegin(GL_QUADS);
	GLfloat x = - size/2.0;
	GLfloat y = - size/2.0;
	GLfloat z = - size/2.0;
	
	GLfloat a[3] = {x, y, z};
	GLfloat b[3] = {x, y, z};
	GLfloat c[3] = {x+size, y, z};
	GLfloat d[3] = {x, y, z};
	
	GLfloat colors[6][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
		{0.0, 0.0, 1.0}, {1.0, 1.0, 0.0}, {0.0, 1.0, 1.0}, {1.0, 0.0, 1.0}};
	 */
}
