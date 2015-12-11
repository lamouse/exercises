#include <stdio.h>
#include <stdlib.h>
#include "AVLTree.h"

#define MAX(a,b) ((a)>(b)?(a):(b))

static int nodeHeight(pavl p);
static pavl singleRotateWithLeft(pavl k2);
static pavl singleRotateWithRight(pavl k2);
static pavl doubleRotateWithLeft(pavl k3);
static pavl doubleRotateWithRight(pavl k3);

pavl init(void){
	pavl pTree = malloc(sizeof(struct AVLTree));
	if(pTree == NULL){
		perror("init\n");
		return pTree;
	}
	pTree->left = NULL;
	pTree->right = NULL;
	pTree->height = -2;
}

pavl insert(pavl p, Element e){
	if(p!=NULL&&(p->height == -2)){
		p->element = e;
		p->height = 0;
		return p;
	}
	if(p == NULL){
		p = malloc(sizeof(struct AVLTree));
		if(p == NULL){
			perror("insert malloc\n");
			return NULL;
		}
		else{
			p->left = p->right = NULL;
			p->element = e;
			p->height = 0;
		}
	}
	else if(e < p->element){
		p->left = insert(p->left,e);
		if(nodeHeight(p->left) - nodeHeight(p->right) == 2){
			if(e < p->left->element)
				p = singleRotateWithLeft(p);
			else
				p = doubleRotateWithLeft(p);
		}
	}
	else if(e > p->element){
		p->right = insert(p->right,e);
		if(nodeHeight(p->right) - nodeHeight(p->left) == 2){
			if(e > p->right->element)
				p = singleRotateWithRight(p);
			else
				p = doubleRotateWithRight(p);
		}
	}
	//e is in the tree do nothing
	p->height = MAX(nodeHeight(p->left), nodeHeight(p->right)) + 1;
	return p;
}

bool isEmpty(pavl p){
	return p->height == -1 || p == NULL;
}

void makeEmpty(pavl p){
	if(p != NULL){
		makeEmpty(p->left);
		makeEmpty(p->right);
		free(p);
	}
}

pavl find(pavl p, Element e){
	if(p == NULL)
		return p;
	if(p->element = e){
		return p;
	}
	if(p->element < e)
		return find(p->left, e);
	if(p->element > e){
		return find(p->right,e);
	}
}

pavl findMax(pavl p){
	if(p != NULL){
		while(p->right != NULL)
			p = p->right;
	}
	return p;
}

pavl findMin(pavl p){
	if(p != NULL){
		while(p->left != NULL)
			p = p->left;
	}
	return p;
}

pavl deleteOne(pavl p, Element e){
	if(p == NULL)
		return NULL;
	if(e < p->element){
		p->left = deleteOne(p->left,e);
		if(nodeHeight(p->right)-nodeHeight(p->left) == 2){
			pavl t = p->right;
			if(nodeHeight(t->left) > nodeHeight(t->right)){
				p = doubleRotateWithRight(p);
			}
			else{
				p = singleRotateWithRight(p);
			}
		}
		else{
			p->height = MAX(nodeHeight(p->left), 
				nodeHeight(p->right)) + 1;
		}
	}
	else if( e > p->element){
		p->right = deleteOne(p->right,e);
		if(nodeHeight(p->left) - nodeHeight(p->right) == 2){
			pavl t = p->left;
			if(nodeHeight(t->right) > nodeHeight(t->left)){
				p = doubleRotateWithLeft(p);
			}
			else{
				p = singleRotateWithLeft(p);
			}
		}
		else
			p->height = MAX(nodeHeight(p->left), 
				nodeHeight(p->right))+1;
	}
	else{
		if(p -> left && p->right){
			if(nodeHeight(p->left) > nodeHeight(p->right)){
				p->element = findMax(p->left)->element;
				p->left = deleteOne(p->left, p->element);
			}
			else{
				p->element = findMin(p->right)->element;
				p->right = deleteOne(p->right, p->element);
			}
		}
		else{
			pavl old = p;
			p = (p->left) ? p->left : p->right;
			free(old);
			old = NULL; 
		}
	}
	return p;
}

void traval(pavl p, void (*fun)(Element e)){
	if(p != NULL){
		traval(p->left, fun);
		fun(retrieve(p));
		traval(p->right, fun);
	}
}

static int nodeHeight(pavl p){
	if(p == NULL)
		return -1;
	else
		return p->height;
}

static pavl singleRotateWithLeft(pavl k2){
	pavl k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	k2->height = MAX(nodeHeight(k2->left), 
		nodeHeight(k2->right)) + 1;
	k1->height = MAX(nodeHeight(k1->left), 
		nodeHeight(k1->right)) + 1;
	return k1;
}

static pavl singleRotateWithRight(pavl k2){
	pavl k1;

	k1 = k2->right;
	k2->right = k1->left;
	k1->left = k2;

	k2->height = MAX(nodeHeight(k2->left), 
		nodeHeight(k2->right)) + 1;
	k1->height = MAX(nodeHeight(k1->left), 
		nodeHeight(k1->right)) + 1;
	return k1;
}

static pavl doubleRotateWithLeft(pavl k3){
	k3->left = singleRotateWithRight(k3->left);
	return singleRotateWithLeft(k3);
}

static pavl doubleRotateWithRight(pavl k3){
	k3->right = singleRotateWithLeft(k3->right);
	return singleRotateWithRight(k3);
}

Element retrieve(pavl p){
	return p->element;
}