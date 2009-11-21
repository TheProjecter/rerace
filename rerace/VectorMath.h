/*
 *  VectorMath.h
 *  rerace
 *
 *  Created by Andrew Wagner on 10/26/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

void turnVector(float* v, float x, float y);
float dotProduct(float* v, float x, float y, float z);
float crossProductX(float a0, float a1, float a2, float* v);
float crossProductY(float a0, float a1, float a2, float* v);
float crossProductZ(float a0, float a1, float a2, float* v);
void cross(float* a, float* b, float* c);
void normalize(float* v);
