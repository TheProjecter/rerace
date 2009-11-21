/*
 *  VectorMath.cpp
 *  rerace
 *
 *  Created by Andrew Wagner on 10/26/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include "VectorMath.h"
#include <Math.h>

void turnVector(float* v, float x, float y)
{
	
	float newX = cos(y*M_PI/180)*v[0] - sin(y*M_PI/180)*v[2];
	float newZ = sin(y*M_PI/180)*v[0] + cos(y*M_PI/180)*v[2];
	
	v[0] = newX;
	v[2] = newZ;
	
	/*float newY = cos(x*M_PI/180)*v[1] - sin(x*M_PI/180)*v[2];
		  newZ = sin(x*M_PI/180)*v[1] + cos(x*M_PI/180)*v[2];
	
	if(newY < 1)
	{
		v[1] = newY;
		v[2] = newZ;
	}*/
}
void rotateVectorAroundVector(float* v, float* rv, float angle)
{
	float vNewView[3] = {0,0,0};
	
	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);
	
	// x position of the new rotated point
	
	
	vNewView[0] = (cosTheta + (1 - cosTheta) * rv[0] * rv[0])		* v[0];
	vNewView[0]	+= ((1 - cosTheta) * rv[0] * rv[1] - rv[2] * sinTheta)	* v[1];
	vNewView[0]  += ((1 - cosTheta) * rv[0] * rv[2] + rv[1] * sinTheta)	* v[2];
	
	// y position of the new rotated point
	
	
	vNewView[1]  = ((1 - cosTheta) * rv[0] * rv[1] + rv[2] * sinTheta)	* v[0];
	vNewView[1] += (cosTheta + (1 - cosTheta) * rv[1] * rv[1])		* v[1];
	vNewView[1] += ((1 - cosTheta) * rv[1] * rv[2] - rv[0] * sinTheta)	* v[2];
	
	// z position of the new rotated point
	
	
	vNewView[2]   = ((1 - cosTheta) * rv[0] * rv[2] - rv[1] * sinTheta)	* v[0];
	vNewView[2]  += ((1 - cosTheta) * rv[1] * rv[2] + rv[0] * sinTheta)	* v[1];
	vNewView[2]  += (cosTheta + (1 - cosTheta) * rv[2] * rv[2])		* v[2];
	
	v[0]=vNewView[0];
	v[1]=vNewView[1];
	v[2]=vNewView[2];
}

float dotProduct(float* v, float x, float y, float z)
{
	return v[0]*x + v[1]*y + v[2]*z;
}
float crossProductX(float a0, float a1, float a2, float* v)
{
	return a1*v[2]-a2*v[1];
}
float crossProductY(float a0, float a1, float a2, float* v)
{
	return -a0*v[2]+a2*v[0];
}
float crossProductZ(float a0, float a1, float a2, float* v)
{
	return a0*v[1]-a1*v[0];
}

void cross(float* a, float* b, float* c)
{
	c[0] = a[1]	*b[2]-a[2]*b[1];
	c[1] = -a[0]*b[2]+a[2]*b[0];
	c[2] = a[0]	*b[1]-a[1]*b[0];
}

void normalize(float* v)
{
	float mag = sqrtf( powf(v[0], 2) + powf(v[1], 2) + powf(v[2], 2) );
	v[0] /= mag;
	v[1] /= mag;
	v[2] /= mag;
}