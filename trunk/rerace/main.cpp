#include <iostream>
#include <GLUT/glut.h>

void display(void)
{
	/* clear window */
	
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	/* draw unit square polygon */
	glBegin(GL_POLYGON);
	glColor3f(1.,0.,0.);
	glVertex3f(-.05, -.05, -.5);
	glVertex3f(-.05, .05);
	glVertex3f(.05, .05);
	glVertex3f(.05, -.05);
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