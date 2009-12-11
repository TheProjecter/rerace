/*
 *  DrawingObjects.cpp
 *  rerace
 *
 *  Created by Keith Thompson on 12/10/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "DrawingObjects.h"
#include "glm.h"
#include "Racer.h"
#include "Guardian.h"
#include <iostream>

GLuint _racerList;
GLuint _guardianList;
GLuint _rockList;
GLuint textureRock;

using namespace std;

GLuint LoadTextureRAW( const char * filename, int width, int height, int wrap, bool transparent )
{
	
	GLuint texture;
	char * data;	
	FILE * file;
	// open texture data
	file = fopen(filename, "rb");
	if ( file==NULL ) {
		cerr << "Could not open texture: " << filename << endl;
		exit(1);
	}
	// allocate buffer
	data = (char*)malloc( width * height * (transparent?4:3) );
	// read texture data
	fread( data, width * height * (transparent?4:3), 1, file );
	fclose( file );
	// allocate a texture name
	glGenTextures( 1, &texture );
	// select our current texture
	glBindTexture( GL_TEXTURE_2D, texture );
	// select modulate to mix texture with color for shading
	gluBuild2DMipmaps( GL_TEXTURE_2D, transparent ? GL_RGBA : 3, width, height, transparent ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data );
	free( data );
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S , GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_CLAMP);

	//glBindTexture(GL_TEXTURE_2D, NULL);
	return texture;
	
} 

void loadRacer()
{	
	string model_name = "data/porsche.obj";
	
	GLMmodel* pmodel;
	pmodel = glmReadOBJ(model_name.c_str());
	if(!pmodel) return;
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    glmScale(pmodel, .2);
	_racerList = glmList(pmodel, GLM_SMOOTH | GLM_MATERIAL, NULL);
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
    glmScale(pmodel, .2);
	_guardianList = glmList(pmodel, GLM_SMOOTH | GLM_MATERIAL, NULL);
}

void loadRock(){
	string model_name = "data/Stone_Forest_1.obj";
	GLuint textureRock = LoadTextureRAW("S1Diffus.raw", 2048, 2048, true, false);
	
	GLMmodel* pmodel;
	pmodel = glmReadOBJ(model_name.c_str());
	if(!pmodel) return;
	glmUnitize(pmodel);
	glmFacetNormals(pmodel);
	glmVertexNormals(pmodel, 90.0);
    glmScale(pmodel, .8);
	glBindTexture(GL_TEXTURE_2D, textureRock);
	_rockList = glmList(pmodel, GLM_SMOOTH | GLM_TEXTURE, textureRock);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

GLuint loadField(){
	loadRock();
	GLuint list;
	GLfloat x,y,z;
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
	for (int i=0; i<150; i++) {
		x = (GLfloat)((rand()%6000)-3000)/100.0f;
		y = (GLfloat)((rand()%6000)-3000)/100.0f;
		z = (GLfloat)((rand()%6000)-3000)/100.0f;
		
		glPushMatrix();
		glTranslatef(x, y, z);
		glRotated(rand()%359, 1, 0, 0);
		glRotated(rand()%359, 0, 1, 0);
		glRotated(rand()%359, 0, 0, 1);
		//float scale = rand()%100+50)/100.0f;
		glScaled((rand()%100+50)/100.0f, (rand()%100+50)/100.0f, (rand()%100+50)/100.0f);
		drawRock();
		glTranslatef(-x, -y, -z);
		glPopMatrix();
	}
	glEndList();
	return list;
}
void drawRock(){
	

	glBindTexture(GL_TEXTURE_2D, textureRock);
	glCallList(_rockList);
	glBindTexture(GL_TEXTURE_2D, NULL);

}

void drawRacer(void* racer)
{
	GLfloat spot_direction[] = {0,0,1};
	GLfloat light0_position[] = { 0.0, 0.0, -0.6, 1.0 };
	
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 18.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 7.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);


	glCallList(_racerList);
}
void drawGuardian(void* guardian)
{

	GLfloat spot_direction[] = {0,0,1};
	GLfloat light1_position[] = { 0.0, 0.0, -0.6, 1.0 };
	
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 18.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	
	glCallList(_guardianList);
}