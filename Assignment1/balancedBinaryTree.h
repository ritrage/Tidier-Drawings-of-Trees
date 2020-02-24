#pragma once
#include <vector>

using namespace std;

typedef struct node {
	int info;
	struct node* llink;
	struct node* rlink;
	struct node* father;
	int level;
	int xcoord;
	int ycoord;
	int offset;
	bool thread;
};

typedef struct extreme {
	node* addr;
	int off;
	int lev;
};

class balancedBinaryTree {
private:
	node* root;
	void makebbt(vector <int>&, int, int, int);
	void initializer(vector <int>&, int n);
	void drawTree(int cx, int xy, node* N);
public:
	balancedBinaryTree(int n);
	void makebbt2();
	void drawIt(node* n);
};