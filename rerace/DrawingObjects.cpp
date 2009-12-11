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
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	GLfloat light_position[] = {0, 0, -0.2};
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
		
	//glEnable(GL_LIGHTING);
	/*glEnable(GL_LIGHT0);
	glMatrixMode(GL_PROJECTION);
	
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	float direction[3] = {0,0,1};
	//GLfloat light_position[] = { 0.0, 0.0, 0.0 };
	glShadeModel (GL_SMOOTH);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, ((Racer*)racer)->location());
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0f);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 0.0f);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, ((Racer*)racer)->heading()); 
	
	
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	glMatrixMode(GL_MODELVIEW);
	 */
	glCallList(_racerList);
}
void drawGuardian(void* guardian)
{
	glCallList(_guardianList);
}