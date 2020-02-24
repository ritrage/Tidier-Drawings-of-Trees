#include "balancedBinaryTree.h"
#include "bresenhamLine.h"
#include "midpointCircle.h"
#include<iostream>
#include <math.h>
#include <gl/glew.h>
#include <GL/GL.h>
#include<cstdlib>
#include <GL/glut.h>
#include <vector>
#include <time.h>
#define rr 10
#define MINSEP 50
#define YSCALE 30

using namespace std;

void calcOffsets(node* root, int level, extreme& rmost, extreme& lmost) {
	node* left;
	node* right;
	extreme LR, LL, RR, RL;
	int CURsep, ROOTsep, LOffsum, ROffsum;
	if (root == NULL) {
		lmost.lev = -1;
		rmost.lev = -1;
	}
	else {
		root->ycoord = level;
		left = root->llink;
		right = root->rlink;
		calcOffsets(left, level + 1, LR, LL);
		calcOffsets(right, level + 1, RR, RL);
		if (left == NULL && right == NULL) {
			rmost.addr = root;
			lmost.addr = root;
			rmost.lev = level;
			lmost.lev = level;
			rmost.off = 0;
			lmost.off = 0;
			root->offset = 0;
		}
		else {
			CURsep = MINSEP;
			ROOTsep = MINSEP;
			LOffsum = 0;
			ROffsum = 0;
			while (left != NULL && right != NULL) {
				if (CURsep < MINSEP) {
					ROOTsep = ROOTsep + (MINSEP - CURsep);
					CURsep = MINSEP;
				}
				if (left->rlink != NULL) {
					LOffsum = LOffsum + left->offset;
					CURsep = CURsep - left->offset;
					left = left->rlink;
				}
				else {
					LOffsum = LOffsum - left->offset;
					CURsep = CURsep + left->offset;
					left = left->llink;
				}
				if (right->llink != NULL) {
					ROffsum = ROffsum - right->offset;
					CURsep = CURsep - right->offset;
					right = right->llink;
				}
				else {
					ROffsum = ROffsum + right->offset;
					CURsep = CURsep + right->offset;
					right = right->rlink;
				}
			}
			root->offset = (ROOTsep + 1) / 2;
			LOffsum = LOffsum - root->offset;
			ROffsum = ROffsum + root->offset;
			if (RL.lev > LL.lev || root->llink == NULL) {
				lmost = RL;
				lmost.off = lmost.off + root->offset;
			}
			else {
				lmost = LL;
				lmost.off = lmost.off - root->offset;
			}
			if (LR.lev > RR.lev || root->rlink == NULL) {
				rmost = LR;
				rmost.off = rmost.off - root->offset;
			}
			else {
				rmost = RR;
				rmost.off = rmost.off + root->offset;
			}
			if (left != NULL && left != root->llink) {
				(RR.addr)->thread = true;
				(RR.addr)->offset = abs((RR.off + root->offset) - LOffsum);
				if ((LOffsum - root->offset) <= RR.off) {
					(RR.addr)->llink = left;
				}
				else {
					(RR.addr)->rlink = left;
				}
			}
			else if (right != NULL && right != root->rlink) {
				(LL.addr)->thread = true;
				(LL.addr)->offset = abs((LL.off - root->offset) - ROffsum);
				if ((ROffsum + root->offset) >= LL.off) {
					(LL.addr)->rlink = right;
				}
				else {
					(LL.addr)->llink = right;
				}
			}
		}
	}
}

void balancedBinaryTree::makebbt(vector <int>& a, int start, int finish, int beg = 0) {
	if (start > finish) return;
	int mid = (start + finish) / 2;
	a[beg] = mid;
	makebbt(a, start, mid - 1, beg + 1);
	makebbt(a, mid + 1, finish, mid - start + beg + 1);
}

void balancedBinaryTree::initializer(vector<int>& input, int n) {
	root->info = input[0];
	root->father = NULL;
	root->level = 0;
	for (int i = 1; i < n; i++) {
		node* temp = new node;
		temp->llink = NULL;
		temp->rlink = NULL;
		temp->info = input[i];
		node* current = this->root, *parent;
		parent = current;
		while (current != NULL) {
			parent = current;
			if (temp->info >= current->info)
				current = current->rlink;
			else
				current = current->llink;
		}
		if (parent!=NULL && (temp->info >= parent->info))
			parent->rlink = temp;
		else if(parent!=NULL)
			parent->llink = temp;
		temp->father = parent;
		if(parent!=NULL)
			temp->level = parent->level + 1;
	}
}

balancedBinaryTree::balancedBinaryTree(int n) {
	node* N = new node;
	root = N;
	root->llink = NULL;
	root->rlink = NULL;
	root->thread = false;
	vector <int> arr(10000000);
	makebbt(arr, 0, n - 1);
	this->initializer(arr, n);
}

void balancedBinaryTree::drawIt(node* N) {
	if (N == NULL) return;
	drawIt(N->llink);
	drawIt(N->rlink);
}

void balancedBinaryTree::drawTree(int cx = 0, int cy = 0, node* N = NULL) {
	if (N == NULL) N = root;
	int dx = N->xcoord;
	int dy = (N->ycoord)*YSCALE-200;
	if (cx == 0 && cy == 0) {
		cx = dx;
		cy = dy;
	}
	if (N->llink != NULL)
		drawTree(dx, dy, N->llink);
	if (N->rlink != NULL)
		drawTree(dx, dy, N->rlink);
	if (N->llink == NULL && N->rlink == NULL) {
		//line(dx - rr, dy, dx, dy + rr);
		//line(dx, dy + rr, dx + rr, dy);
		//line(dx + rr, dy, dx, dy - rr);
		//line(dx, dy - rr, dx - rr, dy);

		circle(dx, dy, rr);
	}
	else {
		circle(dx, dy, rr);
	}
	line(dx, dy, cx, cy);
}

void petrify(node* root, int col) {
	if (root != NULL) {
		root->xcoord = col;
		if (root->thread == true) {
			root->thread = false;
			root->llink = NULL;
			root->rlink = NULL;
		}
		petrify(root->llink, col - root->offset);
		petrify(root->rlink, col + root->offset);
	}
}

void balancedBinaryTree::makebbt2() {
	glPointSize(2.0);
	extreme rmost, lmost;
	calcOffsets(root, 0, rmost, lmost);
	petrify(root, 0);
	drawTree();
}