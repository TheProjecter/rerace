/*
 *  Course.h
 *  rerace
 *
 *  Created by Andrew Wagner and Keith Thompson on 10/28/09.
 *  Copyright 2009 Digital Assertion. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>

typedef struct Point {
	GLfloat x;
	GLfloat y;
	GLfloat c1x;
	GLfloat c1y;
	GLfloat c2x;
	GLfloat c2y;
};

class Course
{
public:
	Course(int levelNum);
	
	void draw();
	
private:
	Point*	_points;
	unsigned int _pointCount;
};
