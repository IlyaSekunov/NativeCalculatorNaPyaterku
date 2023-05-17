#ifndef stackH
#define stackH
#include <complex.h>
#include <stdlib.h>
#define EMPTY 0
#define FULL 1

typedef struct RPNNode {
	int type;
	union {
		_Lcomplex complex_number;
		long double real_number;
		int function;
	};
}RPNNode;

typedef struct stackList {
	RPNNode* value;
	struct stackList* link;
} stackList;

typedef struct STACK {
	stackList* stack;
	void (*push)(struct STACK*, long double);
	RPNNode (*pop)(struct STACK*);
	int (*empty)(struct STACK);
	int size;
	RPNNode (*top)(struct STACK);
	void (*print)(struct STACK);
} STACK;

void stackPush(STACK* stack, long double value) {
	stackList* newList = (stackList*)malloc(sizeof(stackList));
	if (newList) {
		newList->value = value;
		newList->link = stack->stack;
		if (!stack->stack) {
			stack->stack = newList;
			++(stack->size);
			return;
		}
		stack->stack = newList;
		++(stack->size);
	}
	return;
}

long double stackPop(STACK* stack) {
	if (!stack->stack) return (long double)ERR;
	stackList* tmp = stack->stack->link;
	long double value = stack->stack->value;
	free(stack->stack);
	stack->stack = tmp;
	--(stack->size);
	return value;
}

int stackEmpty(STACK stack) {
	if (stack.stack) return FULL;
	return EMPTY;
}

long double stackTop(STACK stack) {
	if (!stack.stack) return (long double)ERR;
	return stack.stack->value;
}

void stackPrint(STACK stack) {
	if (!stack.stack) return;
	while (stack.stack) {
		printf("<- %lf ", stack.stack->value);
		stack.stack = stack.stack->link;
	}
	printf("\n");
	return;
}

void initSTACK(STACK* stack) {
	stack->stack = NULL;
	stack->pop = stackPop;
	stack->push = stackPush;
	stack->empty = stackEmpty;
	stack->size = 0;
	stack->top = stackTop;
	stack->print = stackPrint;
	return;
}


#endif 