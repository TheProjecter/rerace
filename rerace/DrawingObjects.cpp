/*
 *  DrawingObjects.cpp
 *  rerace
 *
 *  Created by Keith Thompson on 12/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "DrawingObjects.h"
#include <GLUT/GLUT.h>
#include "glm.h"

#include "Racer.h"
#include "Guardian.h"

GLuint _displayList;

void loadRacer()
{
	string model_name = "data/porsche.obj";
	
	GLMmodel* pmodel;
	pmodel = glmReadOBJ(model_name.c_str());
	if(!pmodel) return;
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    glmScale(pmodel, .1);
	_displayList = glmList(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}
void loadGuardian()
{
	glCallList(_displayList);
}


void drawRacer(void* racer)
{
	//glEnable(GL_LIGHTING);
	
	glMatrixMode(GL_PROJECTION);
	glEnable(GL_LIGHT0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 10.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0f);
	float position[3] = {0, 0, -20};
	float direction[3] = {0,0,1};
	float light_diffuse[4] = {0.5f, 0.5f, 0.5f, 1.0f};
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_diffuse); 
	glLightfv(GL_LIGHT0, GL_POSITION, position); 
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction); 
	glMatrixMode(GL_MODELVIEW);  
	//glDisable(GL_LIGHTING);
	//glutSolidCube(.1);
	//drawCube(.1);
	
	glCallList(_displayList);
}
void drawGuardian(void* guardian)
{
	string model_name = "data/f-16.obj";
	
	GLMmodel* pmodel;
	pmodel = glmReadOBJ(model_name.c_str());
	if(!pmodel) return;
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    glmScale(pmodel, .1);
	_displayList = glmList(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}