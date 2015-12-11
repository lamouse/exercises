#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVLTree.h"

void print(Element e){
	printf("%d ", e);
}

int main(int argc, char const *argv[])
{
	pavl p;
	p = init();
	srand(time(NULL));

	for(int i = 0; i < 20; i++)
		p = insert(p, i);

	traval(p, print);
	for(int i = 8; i < 20; i++)
		p = deleteOne(p,i);
	printf("\n");
	traval(p, print);
	makeEmpty(p);
	printf("\n");
	return 0;
}