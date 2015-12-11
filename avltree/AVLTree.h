#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdbool.h>

typedef int Element;
typedef struct AVLTree* pavl;

struct AVLTree{
	Element element;
	pavl left;
	pavl right;
	int height;
};

pavl init(void);
pavl insert(pavl p, Element e);
bool isEmpty(pavl p);
void makeEmpty(pavl p);
pavl deleteOne(pavl p, Element e);
pavl find(pavl p, Element e);
pavl findMin(pavl p);
pavl findMax(pavl p);
void traval(pavl p, void (*fun)(Element e));
Element retrieve(pavl p);
#endif