#include <iostream>
#include <GLUT/glut.h>
#include <ApplicationServices/ApplicationServices.h>

#include "GameController.h"
#include "constants.h"

GameController* gameController;
ViewController* viewController;

int width = 0;
int height = 0;
int lastPoint[2] = {-1, -1};

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
	width = w;
	height = h;
	
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	
	gluPerspective(60.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
	//glRotatef(45, 1, 0, 0);
	//glRotatef(45, 0, 1, 0);
	//glRotatef(45, 0, 0, 1);
	//glTranslatef(1, 0, 0);
	
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}
void passiveMouseFunction(int x, int y)
{
	lastPoint[0]=x;
	lastPoint[1]=y;
	//viewController->mouseMove((float)(width/2.0-x)/(float)width, (float)(height/2.0-y)/(float)height);
	//gameController->mouseMove((float)(width/2.0-x)/(float)width, (float)(height/2.0-y)/(float)height);
}
void timerFunction(int extra)
{
	gameController->mainLoop(lastPoint[0],lastPoint[1]);
	
	glutPostRedisplay();
	glutTimerFunc(kGameSpeed,timerFunction,0);
}
void keyboardFunction(unsigned char key, int x, int y)
{
	gameController->keyboardFunction(key, x, y);
}

int main (int argc, char** argv) {
    
	/* Initialize mode and open a window in upper left corner of screen */
	/* Window title is name of program (arg[0]) */
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutCreateWindow(argv[0]);
	
	// Callback Functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(kGameSpeed, timerFunction,0);
	glutPassiveMotionFunc(passiveMouseFunction);
	glutKeyboardFunc(keyboardFunction);
	
	// Properties
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutWarpPointer(width/2, height/2);
	
	//CGEventSourceSetLocalEventsSuppressionInterval(,0.0);
	CGSetLocalEventsSuppressionInterval(0.0);
	
	// Setup Objects
	viewController = new ViewController();
	gameController = new GameController(viewController);
	
	// Start Main Loop
	glutMainLoop();
	
    return 0;
}