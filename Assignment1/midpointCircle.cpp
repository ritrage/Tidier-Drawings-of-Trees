#include "midpointCircle.h"
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>
/**
Midpoint circle implementation
*/

int xp, yp;

void drawCircle(int, int);

void drawPixel(GLint x, GLint y) {
	//glColor3f(1.0, 0.0, 0.0);
	//glPointSize(2.0);
	//glBegin(GL_POINTS);
	glVertex2i(800-x, 500-y);
	//glEnd();
}

void circle(int xiii, int yiii, int r) {
	xp = xiii; yp = yiii;
	int x = 0;
	int y = r;
	int d = 1 - r;
	int deltaE = 3;
	int deltaSE = -2 * r + 5;
	drawCircle(x, y);
	while (y > x) {
		if (d < 0) {
			d += deltaE;
			deltaE += 2;
			deltaSE += 2;
		}
		else {
			d += deltaSE;
			deltaE += 2;
			deltaSE += 4;
			y--;
		}
		x++;
		drawCircle(x, y);
	}
}

void drawCircle(int x, int y) {
	drawPixel(x+ xp, y+ yp);
	drawPixel(xp- x, yp+ y);
	drawPixel(x+xp, yp-y);
	drawPixel (xp - x,yp -y);
	drawPixel(xp+y, yp+x);
	drawPixel(xp-y, yp+x);
	drawPixel(xp+y, yp-x);
	drawPixel(xp-y, yp-x);
}