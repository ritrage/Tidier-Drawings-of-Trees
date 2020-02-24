#include <iostream>
#include<math.h>
#include "balancedBinaryTree.h"
#include "midpointCircle.h"
#include "bresenhamLine.h"
#include <gl/glew.h>
#include <GL/GL.h>
#include <GL/glut.h>
#include <Windows.h>

/**
*	@author Ritwik Sharma 2017A7PS0242H
*			Rahul Pillai 2017A7PS0099H
*			Kandula Mohan Krishna 2017A7PS0053H
*/

void init() {
	glClearColor(0, 0, 0, 1);

}

balancedBinaryTree* bbt;
int n;

void drawOnPaper();

void reshape(int, int);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1600, 1000);

	cout << "Enter the number of nodes for the tree"<<endl;
	cin >> n;
	bbt = new balancedBinaryTree(n);
	glutCreateWindow("Window 1");
	glutDisplayFunc(drawOnPaper);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}



void drawOnPaper() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	
	glBegin(GL_POINTS);
	bbt->makebbt2();
	//line(0,200,100,0);
	glEnd();
	glFlush();
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,w,0, h);
	glMatrixMode(GL_MODELVIEW);
}