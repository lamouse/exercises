#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

#define MAXLEN 512
#define ERRLEN 100

char errmsg[ERRLEN] = {0};
void pretreament(char expression[], size_t ex_len);
void push_num(Stack *s, const char* str, int * n);
double pop_num(Stack *s);
void caiculated(Stack *s, char ch, double num);
void put_num(Stack *s, double num);
double caiculated_result(const char str[], size_t len);

int main(int argc, char *argv[]){
	char str[MAXLEN] = {0};
	double result = 0;;
	
	fgets(str, MAXLEN, stdin);
	if(str[0] == '\n'){
		printf("please input a expression\n");
		exit(EXIT_FAILURE);
	}

	pretreament(str, strlen(str));
	if(errmsg[0] != 0){
		printf("%s\n", errmsg);
		exit(EXIT_FAILURE);
	}
#ifndef NODEBUG
	printf("%s\n", str);
#endif

	result = caiculated_result(str, strlen(str));
	if (result == (int)result)
	{
		printf("=%d\n", (int)result);
	}
	else
		printf("=%f\n", result);

	return 0;
}

void push_num(Stack *s, const char* str, int *n){
	int i = *n;
	if(str[i] == '-')
		i++;
	
	int tmp;

	for(; isdigit(str[i]) || str[i] == '.'; i++)
		;
	tmp = i;
	--i;
	for(; i >= *n; i--){
		push(s,str[i]);
	}
#ifndef NODEBUG
	printf("push_num count %d value=%s\n",s->count, s->stack);
#endif
	*n = tmp;
}

double pop_num(Stack *s){
	char temp[16]={'\0'};
	int i = 1;
#ifndef NODEBUG
	printf("pop_num star count=%d value=%s\n",s->count, s->stack);
#endif
	temp[0] = top(s);
	pop(s);
	while((isdigit(top(s)) || top(s) == '.')&&!is_empty(s)){
		temp[i++] = top(s);	
		pop(s);
	}
	temp[i] = '\0';
#ifndef NODEBUG
	printf("pop_num end count=%d value=%s\n",s->count, s->stack);
#endif
	return atof(temp);
}

void put_num(Stack *s, double num){
	char buf[16] = {'\0'};
	if(num == (int)num)
		snprintf(buf,15,"%d", (int)num);
	else
		snprintf(buf,15,"%f", num);

	for(int i = strlen(buf)-1; i >=0; i--){
		push(s, buf[i]);
	}
}

void caiculated(Stack *s, char ch, double num){
	double tmp;
	double num_temp = num;
	char operatored = ch;
	if(!is_empty(s)){
		if(operatored == '('){
			if(is_empty(s))
				return;
			operatored = top(s);

			pop(s);
		}
		tmp = pop_num(s);
		if(operatored==0){
			if (is_empty(s))
			{
				put_num(s,tmp);
				return;
			}
			else{
				operatored = top(s);
				if(operatored == '('){
					put_num(s,tmp);
					return;
				}
				pop(s);
				num_temp = tmp;
				tmp = pop_num(s);
			}
		}		
	}
	else
		return;

#ifndef NODEBUG
			printf("caiculated operatored %c\n", operatored);
#endif
	
	switch(operatored){
		case '+':
			put_num(s,tmp + num_temp);
			break;
		case '-':
			put_num(s, tmp - num_temp);
			break;
		case '*':
			put_num(s, tmp * num_temp);
			break;
		case '/':
			if (!num_temp)
			{
				printf("divided 0 err\n");
				exit(EXIT_FAILURE);
			}
			put_num(s, tmp / num_temp);
			break;
		default :
			printf("%c is not arithmetic operator\n", operatored);
			return;
	}
}

void pretreament(char expression[], const size_t ex_len){
	char str[MAXLEN] = {0};
	int parentheses = 0;
	for(int i = 0,j = 0; i < ex_len; i++){
		if(isspace(expression[i]))
			continue;
		if (expression[i] == '(')
		{
			++parentheses;
		}
		if(expression[i] == ')')
			--parentheses;
		switch(expression[i]){
			case '0' :
			case '1' :
			case '2' :
			case '3' :
			case '4' :
			case '5' :
			case '6' :
			case '7' :
			case '8' :
			case '9' :
			case '+' :
			case '-' :
				if((str[j-1] == '+' || str[j-1] == '-' || str[j-1] == '*' || str[j-1] == '/') && expression[i] == '+')
					break;
				str[j++] = expression[i]; 
				break;
			case '.' :
				if(j>0&&str[j - 1] == '.'){
					snprintf(errmsg, ERRLEN-1, "expression err '..'");
					return;
				}
				
				if (j>0&&!isdigit(str[j-1])){
					str[j++] = '0';
					str[j++] = '.';
					break;
				}
				else if(j == 0){
					str[j++] = '0';
					str[j++] = '.';
					break;
				}
				str[j++] = '.';
				break;
			case '*' :
			case '/' :
				if(str[j-1] == '(' || str[j-1] == '/' || str[j - 1] == '*'||
					str[j-1] == '+'|| str[j-1] == '-' || j == 0){
					snprintf(errmsg, ERRLEN-1, "expression '%c%c' error",j == 0? ' ':str[j-1], expression[i]);
					return;
				}
				str[j++] = expression[i];
				break;
			case '(' :
				str[j++] = expression[i];
				break;
			case ')' :
				if(!isdigit(str[j-1]) && str[j-1] != ')'){
					snprintf(errmsg, ERRLEN-1, "expression '%c%c' error",j == 0? ' ':str[j-1], expression[i]);
					return;
				}

				str[j++] = expression[i];
				break;
				
			case '\n':
				str[j] = '\0';
				break;
	
			default :
			 	strncpy(errmsg, "is not a expression", ERRLEN);
			 	return;
			}
			if(parentheses < 0){
				snprintf(errmsg, ERRLEN-1, "')'more than '('");
				return;
			}
		}
	if(parentheses != 0){
		snprintf(errmsg, ERRLEN-1, "parentheses '%c' more than '%c'", 
			parentheses > 0 ? '(': ')', parentheses > 0 ? ')' : '(');
		return;
	}

	if(str[strlen(str)-1] != ')' && !isdigit(str[strlen(str)-1])){
		if(str[strlen(str)-1] == '.')
			str[strlen(str)-1] = '\0';
		else{
			snprintf(errmsg, ERRLEN-1, "expression end err '%c'", str[strlen(str)-1]);
			return;
		}
	}

	for(int i = 0; i < strlen(str) + 1; i++)
		expression[i] = str[i];
}

double caiculated_result(const char str[], size_t len){
	double num_temp;
	char operatored;
	Stack stack;
	init(&stack);

	int i = 0;
	int m = 0;

	while(1){
		if(isdigit(str[i]))
			push_num(&stack, str, &i);
#ifndef NODEBUG		
		m++;
		if(m > 10)
			return 0;
#endif
		switch(str[i]){
			case '(':
					push(&stack, str[i++]);
				break;
			case ')':
				num_temp = pop_num(&stack);
				operatored = top(&stack);

				if(operatored == '('){
					pop(&stack);
					put_num(&stack,num_temp);
					++i;
					break;
				}
				pop(&stack);
				caiculated(&stack, operatored, num_temp);
				num_temp = pop_num(&stack);
				if(top(&stack) == '('){
					pop(&stack);
					put_num(&stack, num_temp);
				}
				++i;
				break;
			case '+':
				caiculated(&stack,0,0);
				push(&stack,str[i++]);
				break;
			case '-':		
				if(i==0 || (!isdigit(str[i-1])&&str[i-1] != ')')){
					push_num(&stack, str, &i);
					break;
				}
				caiculated(&stack,0,0);	
				push(&stack,str[i++]);
				break;
			case '*':
			case '/':
				if(str[i+1] == '('){
					push(&stack, str[i++]);
					break;
				}
				operatored = str[i++];
				num_temp = atof(str+i);
				caiculated(&stack,operatored,num_temp);
				caiculated(&stack,0,0);
				if(str[i] == '-')
					i++;
				for(; isdigit(str[i])||str[i]=='.'; i++)
				;
					break;				
			case '\0':
				num_temp = pop_num(&stack);
#ifndef NODEBUG
				printf("num_temp %f\n", num_temp);
#endif
				while(!is_empty(&stack)){
					operatored = top(&stack);
					pop(&stack);
					if(is_empty(&stack)&&operatored=='(')
						break;
					caiculated(&stack,operatored, num_temp);
					num_temp = pop_num(&stack);
				}
				return num_temp;
		}
	}

	return num_temp;
}
