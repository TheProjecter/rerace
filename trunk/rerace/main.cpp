#include <iostream>
#include <GLUT/glut.h>

#include "GameController.h"

GameController* gameController;
ViewController* viewController;


void display(void)
{
	/* clear window */
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	viewController->draw();
	
	/*  Empties all GL buffers, causing all issued commands to be executed
	 as quickly as they are accepted by the actual rendering engine */
	glFlush();
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
				2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
				2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

void timerFunction(int extra)
{
	gameController->mainLoop();
	
	glutPostRedisplay();
	glutTimerFunc(30,timerFunction,0);
}

int main (int argc, char** argv) {
    
	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow(argv[0]);
	
	// Callback Functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(1000, timerFunction,0);
	
	// Properties
	glEnable(GL_DEPTH_TEST);
	
	// Setup Objects
	viewController = new ViewController();
	gameController = new GameController(viewController);
	
	// Start Main Loop
	glutMainLoop();
	
    return 0;
}