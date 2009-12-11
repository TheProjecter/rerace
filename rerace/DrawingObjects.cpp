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

GLuint _racerList;
GLuint _guardianList;

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
	_racerList = glmList(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}
void loadGuardian()
{
	string model_name = "data/f-16.obj";
	
	GLMmodel* pmodel;
	pmodel = glmReadOBJ(model_name.c_str());
	if(!pmodel) return;
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    glmScale(pmodel, .1);
	_guardianList = glmList(pmodel, GLM_SMOOTH | GLM_MATERIAL);
}


void drawRacer(void* racer)
{
	GLfloat spot_direction[] = {0,0,1};
	GLfloat light0_position[] = { 0.0, 0.0, -0.2, 1.0 };
	
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 18.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);


	glCallList(_racerList);
}
void drawGuardian(void* guardian)
{

	GLfloat spot_direction[] = {0,0,1};
	GLfloat light1_position[] = { 0.0, 0.0, -0.2, 1.0 };
	
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 18.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	
	glCallList(_guardianList);
}