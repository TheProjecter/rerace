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

// Initialize All lighting for world
void initLighting(void){

	//Default ambient lighing for models
	GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glShadeModel (GL_SMOOTH);
	
	glEnable(GL_LIGHTING);
	
	//Light0 - racer
	GLfloat light0_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light0_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light0_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	
	glEnable(GL_LIGHT0);
	
	
	//Light1 - guardian
	GLfloat light1_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0);
	
	glEnable(GL_LIGHT1);
	
	
	//Light2 - sky light
	GLfloat light2_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light2_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light2_position[] = { 0.0, 0.0, 0.0, 1.0 };
	
	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0);
	
	glEnable(GL_LIGHT2);

	//Light3 - sky light
	GLfloat light3_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light3_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light3_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light3_position[] = { 0.0, 0.0, -20.0, 1.0 };
	
	glLightfv(GL_LIGHT3, GL_AMBIENT, light3_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light3_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.0);
	
	glEnable(GL_LIGHT3);
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
	/* Windowed
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(kWindowWidth, kWindowHeight);
	glutCreateWindow(argv[0]);
	 */
	
	// Full Screen
	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    // 1440x900, 16bit pixel depth, 60Hz refresh rate
    glutGameModeString( "1440x900:32@60" );
    // start fullscreen game mode
    glutEnterGameMode();
	
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