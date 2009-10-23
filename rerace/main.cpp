#include <iostream>
#include <GLUT/glut.h>

void rect(GLfloat *va, GLfloat *vb, GLfloat *vc, GLfloat *vd)
{
	glVertex3fv(va);
	glVertex3fv(vb);
	glVertex3fv(vc);
	glVertex3fv(vd);
}

void cube(GLfloat *point, GLfloat size)
{
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
    rect(a, b, c, d);
	
	// Left
    glColor3fv(colors[1]);
    rect(a, b, f, e);
	
	// Right
    glColor3fv(colors[2]);
    rect(d, c, g, h);
	
	// Bottom
    glColor3fv(colors[3]);
    rect(e, f, g, h);
	
	// Back
    glColor3fv(colors[4]);
    rect(a, d, h, e);
	
	// Front
    glColor3fv(colors[5]);
    rect(b, c, g, f);
}

void display(void)
{
	/* clear window */
	glRotatef(5, 0, 1, 0);
	glRotatef(5, 0, 0, 1);
	glRotatef(5, 1, 0, 0);
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* draw unit square polygon */
	glBegin(GL_POLYGON);
	GLfloat startPoint[3] = {-.8, -.8, -.8};
	GLfloat startSize = 1.6;
	cube(startPoint, startSize);
	glEnd();
	
	/*  Empties all GL buffers, causing all issued commands to be executed
	 as quickly as they are accepted by the actual rendering engine */
	glFlush();
}

int main (int argc, char** argv) {
    
	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */
	
	glutInit(&argc, argv);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutMainLoop();
	
    return 0;
}