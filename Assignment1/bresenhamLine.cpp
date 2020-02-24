#include "bresenhamLine.h"
#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<GL/glut.h>


void drawPx(int x, int y) {
	glPointSize(2.0);
	glVertex2i(800-x, 500 - y);
}

/**
Bresenham's line drawing algorithm implementation
*/

void line(int xi, int yi, int xii, int yii) {
	if (xii >= xi && yii >= yi) {
		int dx = abs(xii - xi);
		int dy = abs(yii - yi);
		if (dx >= dy) {
			int d = 2 * dy - dx;
			int incrE = 2 * dy;
			int incrNE = 2 * (dy - dx);
			int x = xi;
			int y = yi;
			drawPx(x, y);
			while (x < xii) {
				if (d <= 0) d += incrE;
				else {
					d += incrNE;
					y++;
				}
				x++;
				drawPx(x, y);
			}
		}
		else {
			int d = 2 * dx - dy;
			int incrE = 2 * dx;
			int incrNE = 2 * (dx - dy);
			int x = xi;
			int y = yi;
			drawPx(x, y);
			while (y < yii) {
				if (d <= 0) d += incrE;
				else {
					d += incrNE;
					x++;
				}
				y++;
				drawPx(x, y);
			}
		}
	}
	else if (xii >= xi && yii < yi) {
		int dx = abs(xii - xi);
		int dy = abs(yii - yi);
		if (dx >= dy) {
			int d = 2 * dy - dx;
			int incrE = 2 * dy;
			int incrNE = 2 * (dy - dx);
			int x = xi;
			int y = yi;
			drawPx(x, y);
			while (x < xii) {
				if (d <= 0) d += incrE;
				else {
					d += incrNE;
					y--;
				}
				x++;
				drawPx(x, y);
			}
		}
		else {
			int d = 2 * dx - dy;
			int incrE = 2 * dx;
			int incrNE = 2 * (dx - dy);
			int x = xii;
			int y = yii;
			drawPx(x, y);
			while (y < yi) {
				if (d <= 0) d += incrE;
				else {
					d += incrNE;
					x--;
				}
				y++;
				drawPx(x, y);
			}
		}
	}
	else line(xii, yii, xi, yi);
}