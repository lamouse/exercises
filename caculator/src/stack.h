#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct Stack{
	char stack[1024];
	int count;
}Stack;

void init(Stack * s);
bool is_full(Stack* s);
bool is_empty(Stack* s);

void push(Stack* s, char ch);
void pop(Stack*  s);
char top(Stack* s);
#endif