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
	
	float newY = cos(x*M_PI/180)*v[1] - sin(x*M_PI/180)*v[2];
		  newZ = sin(x*M_PI/180)*v[1] + cos(x*M_PI/180)*v[2];
	
	if(newY < 1)
	{
		v[1] = newY;
		v[2] = newZ;
	}
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