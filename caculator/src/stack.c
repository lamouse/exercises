#include "stack.h"

void init(Stack *s){
	s->count = -1;
	for(int i = 0; i < sizeof(s->stack); i++)
		s->stack[i] = '\0';
}

void push(Stack *s, char sh){
	if(s->count == sizeof(s->stack))
		return;
	++s->count;
	s->stack[s->count] = sh;
}

bool is_full(Stack *s){
	return s->count >= sizeof(s->stack);
}

bool is_empty(Stack *s){
	return s->stack[0] == '\0';
}

void pop(Stack* s){
	s->stack[s->count] = '\0';
	if(s->count >= 0)
		--s->count;
}

char top(Stack *s){
	return s->stack[s->count];
}