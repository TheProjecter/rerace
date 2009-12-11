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

void initLighting(void){

	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

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
	
    viewController->resetCamera();
	
    glutPostRedisplay();
}
void passiveMouseFunction(int x, int y)
{
	lastPoint[0]=x;
	lastPoint[1]=y;
}
void timerFunction(int extra)
{
	gameController->mainLoop(lastPoint[0],lastPoint[1]);
	
	glutPostRedisplay();
	glutTimerFunc(kGameSpeed,timerFunction,0);
}
void keyboardDownFunction(unsigned char key, int x, int y)
{
	gameController->keyboardDownFunction(key, x, y);
}
void keyboardUpFunction(unsigned char key, int x, int y)
{
	gameController->keyboardUpFunction(key, x, y);
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
	glutKeyboardFunc(keyboardDownFunction);
	glutKeyboardUpFunc(keyboardUpFunction);
	
	// Properties
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	
	initLighting();
	
	//CGEventSourceSetLocalEventsSuppressionInterval(,0.0);
	CGSetLocalEventsSuppressionInterval(0.0);
	// Reset the pointer to the center of the screen
	glutWarpPointer( width/2, height/2 );
	
	// Setup Objects
	viewController = new ViewController();
	gameController = new GameController(viewController);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
	
	// Start Main Loop
	glutMainLoop();
	
    return 0;
}