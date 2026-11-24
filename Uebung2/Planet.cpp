/////////////////////////////////////////////////////////////////////////////
//																									//
// Code framework for lecture computer graphics WS 2025/26 assignment 2  	//
//																									//
// (c) Georg Umlauf																			//
//																									//
/////////////////////////////////////////////////////////////////////////////


#include "Planet.h"
#include "glut.h"
#include <cmath>

//
// Implement HERE your Bresenham algorithm for circles 
//
void Planet::draw() const
{
	{
		const int cx = static_cast<int>(position[0]);
		const int cy = static_cast<int>(position[1]);

		int x = 0;
		int y = radius;
		int d = 3 - 2 * radius;

		glColor3d(color.r, color.g, color.b);
   		glBegin(GL_POINTS);

		while (x <= y) {

			glVertex2i(cx + x, cy + y);
			glVertex2i(cx - x, cy + y);
			glVertex2i(cx + x, cy - y);
			glVertex2i(cx - x, cy - y);

			glVertex2i(cx + y, cy + x);
			glVertex2i(cx - y, cy + x);
			glVertex2i(cx + y, cy - x);
			glVertex2i(cx - y, cy - x);
			x++;

			if (d > 0) {
				y--;
				d = d + 4 * (x - y) + 10;
			} else {
				d = d + 4 * x + 6;
			}
		}

		glEnd();
	}
}

