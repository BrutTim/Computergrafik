/////////////////////////////////////////////////////////////////////////////
//																									//
// Code framework for lecture computer graphics WS 2025/26 assignment 2+3	//
//																									//
// A generic class for n-dimensional coordinate vectors							//
//																									//
// (c) Georg Umlauf																			//
//																									//
/////////////////////////////////////////////////////////////////////////////


#include "Vector.h"
#include "Matrix.h"

#include <iostream>

// maybe you have to switch to your local include path, depending on your GLUT installation
#include "glut.h"
#include "Planet.h"

////////////////////////////////////////////////////////////
//
// system relevant global variables
//

// resolution of the of the main window (can be changed by the user)
int g_WinWidth  = 800;
int g_WinHeight = 800;

// global variable to tune the timer interval
int g_iTimerMSecs;

float planetAngle = 0.0f;
float planetAngleIncrement = 0.01f;

float moonAngle = 0.0f;
float moonAngleIncrement = 0.04f;

//
/////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//
// private, global variables ... REPLACE BY YOUR OWN ONES
//
// some global state variables used to describe ...
float g_iPos;			// ... position and ...
float g_iPosIncr;		// ... position increment (used in display1)

CVec2i g_vecPos;		// same as above but in vector form ...
CVec2i g_vecPosIncr;	// (used in display2)
//
/////////////////////////////////////////////////////////////

// Function to initialize our own variables
void init () 
{
	// init timer interval
	g_iTimerMSecs = 10;

	// init variables for display1
	g_iPos     = 0;
	g_iPosIncr = 2;

	// init variables for display2
	int aiPos    [2] = {0, 0};
	int aiPosIncr[2] = {2, 2};
	g_vecPos.setData (aiPos);
	g_vecPosIncr.setData (aiPosIncr);
}

// Function to initialize the view to ortho-projection.
// Please do not change.
void initGL () 
{
	glViewport (0, 0, g_WinWidth, g_WinHeight);		// Establish viewport to cover entire window.

	glMatrixMode (GL_PROJECTION);					// Start modifying the projection matrix.
	glLoadIdentity ();								// Init projection matrix.
	glOrtho (-g_WinWidth  /2, g_WinWidth  /2,		// Map abstract coords directly to window coords.
			 -g_WinHeight /2, g_WinHeight /2, 0, 1);	
	glDrawBuffer (GL_BACK);							// Tell GL that we draw to the back buffer and swap ...
													// ... buffers when image is ready to avoid flickering	
	float b = 70.0f / 100.0f;
	glClearColor(b, b, b, 1.0f);					// Tell which color to use to clear image
}

// Callback Function to change the window size.
// Please do not change.
void reshape(int w, int h)
{
	g_WinWidth  = w;
	g_WinHeight = h;
	glViewport(0, 0, w, h);							// Establish viewport to cover entire window.

	glMatrixMode(GL_PROJECTION);					// Start modifying the projection matrix.
	glLoadIdentity();								// Reset projection matrix.
	glOrtho(-w / 2, w / 2, -h / 2, h / 2, 0, 1);	// Map abstract coords directly to window coords.

	glutPostRedisplay();
}

// timer callback function
void timer (int value) 
{
	///////
	// UPDATE YOUR VARIABLES HERE ...
	//
	planetAngle += planetAngleIncrement;
    moonAngle += moonAngleIncrement;

	//
	///////

	// These variables are just for the heaving triangles
	int size2 = std::min (g_WinWidth, g_WinHeight) / 2;

	// variables for displayExercise3 ... REPLACE BY YOUR OWN ONES
	if (g_iPos<=-size2 || g_iPos>=size2) g_iPosIncr = -g_iPosIncr;
	g_iPos += g_iPosIncr;

	// variables for displayExercise4 ... REPLACE BY YOUR OWN ONES
	if (g_vecPos[1]<=-size2 || g_vecPos[1]>=size2) g_vecPosIncr = -g_vecPosIncr; 
	g_vecPos += g_vecPosIncr;

	// the last two lines should always be
	glutPostRedisplay ();
	glutTimerFunc (g_iTimerMSecs, timer, 0);	// call timer for next iteration
}

CVec2f rotateAroundOrigin(const CVec2f& point, float angle) {
	CMat2f roation;
	roation(0, 0) = cos(angle);
	roation(0, 1) = -sin(angle);
	roation(1, 0) = sin(angle);
	roation(1, 1) = cos(angle);

	return roation * point;
}

CVec2f rotateAroundPoint(const CVec2f& point, const CVec2f& center, float angle) {
	
	return center + rotateAroundOrigin(point - center, angle);
}

// display callback function for EXERCISE 3
void displayExercise3(void)
{

	glClear (GL_COLOR_BUFFER_BIT);

	///////
	// remove the lines from "glBegin(...)" to "glEnd();" 
	// 
	// and display your planet data of EXERCISE 3 here 
	// using the AFFINE implementation of affine maps.
	//

	Planet sun, planet, moon;
	CVec2f sunPos;

	sunPos[0] = 0.0f;
	sunPos[1] = 0.0f;

	sun.setPosition(sunPos);
	sun.setRadius(30);
	sun.setColor(Color(1.0f, 1.0f, 0.0f));
	sun.draw();

	CVec2f planetStart;
	planetStart[0] = 180.0f;
	planetStart[1] = 0.0f;

	planet.setPosition(rotateAroundOrigin(planetStart, planetAngle));
	planet.setRadius(20);
	planet.setColor(Color(0.0f, 0.0f, 1.0f));
	planet.draw();

	CVec2f moonStart = planet.getPosition();
	moonStart[0] += 50.0f;

	moon.setPosition(rotateAroundPoint(moonStart, planet.getPosition(), moonAngle));
	moon.setRadius(10);
	moon.setColor(Color(1.0f, 0.0f, 0.0f));
	moon.draw();



	// In double buffer mode the last two lines should always be
	glFlush        ();
	glutSwapBuffers(); // swap front and back buffer
}

	CMat3f rotationMatrix(float angle) {
		CMat3f matrix = CMat3f::Identity();
		matrix(0, 0) = cos(angle);
		matrix(0, 1) = -sin(angle);

		matrix(1, 0) = sin(angle);
		matrix(1, 1) = cos(angle);

		return matrix;
	}

	CMat3f rotationAroundPointMatrix(const CVec3f& center, float angle) {
		CMat3f matrix = rotationMatrix(angle);

		matrix(0, 2) = center[0] - (center[0] * cos(angle)) + (center[1] * sin(angle));
		matrix(1, 2) = center[1] - (center[0] * sin(angle)) - (center[1] * cos(angle));

		return matrix;
	}

	void setDrawingPosition(Planet& body, const CVec3f& position)
	{
		CVec2f pixelPosition;
		pixelPosition[0] = position[0] / position[2];
		pixelPosition[1] = position[1] / position[2];

		body.setPosition(pixelPosition);
	}

// display callback function for EXERCISE 4
void displayExercise4(void)
{
	glClear (GL_COLOR_BUFFER_BIT);

	///////
	// remove the lines from "glBegin(...)" to "glEnd();" 
	// 
	// and display your planet data of EXERCISE 4 here 
	// using the HOMOGENEOUS implementation of affine maps.
	//

	Planet sun, planet, moon;

	CVec3f sunPosition(0.0f, 0.0f, 1.0f);
    CVec3f planetStart(180.0f, 0.0f, 1.0f);

	CVec3f planetPosition = rotationMatrix(planetAngle) * planetStart;

	CVec3f moonStart = planetPosition;
	moonStart[0] += 50.0f;

	CVec3f moonPosition = rotationAroundPointMatrix(planetPosition, moonAngle) * moonStart;

	setDrawingPosition(sun, sunPosition);
    sun.setRadius(30);
    sun.setColor(Color(1.0, 1.0, 0.0));
    sun.draw();

    setDrawingPosition(planet, planetPosition);
    planet.setRadius(20);
    planet.setColor(Color(0.0, 0.0, 1.0));
    planet.draw();

    setDrawingPosition(moon, moonPosition);
    moon.setRadius(10);
    moon.setColor(Color(1.0, 0.0, 0.0));
    moon.draw();

	//
	///////

	// In double buffer mode the last two lines should always be
	glFlush        ();
	glutSwapBuffers(); // swap front and back buffer
}

void keyboard (unsigned char key, int x, int y) 
{
	switch (key) {
		case 'q':
		case 'Q':
			exit (0); // quit program
			break;
		case '1':
			glutDisplayFunc (displayExercise3);
			break;
		case '2':
			glutDisplayFunc (displayExercise4);
			break;
		default:
			// do nothing ...
			break;
	};
}

// The main
// Please do not change.
int main (int argc, char **argv) 
{
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutCreateWindow("Computer graphics assignment 2: 2d-Rotations (WS25/26)");
	glutReshapeWindow(g_WinWidth, g_WinHeight);

	init  ();	// init my variables first
	initGL();	// init the GL (i.e. view settings, ...)

	glutTimerFunc(10, timer, 0);
	glutReshapeFunc (reshape);			// is triggered on window size changes
	glutDisplayFunc (displayExercise4);	// is triggered to redraw the viewport/display
	glutKeyboardFunc(keyboard);			// is triggered on keyboard events

	// start main loop
	glutMainLoop ();

	return 0;
}
