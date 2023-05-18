#ifndef stackH
#define stackH
#include <complex.h>
#include <stdlib.h>
#include <stdio.h>
#include "Constants.h"

typedef struct RPNNode {
	int type;
	union {
		_Lcomplex complex_number;
		long double real_number;
		int function;
	};
}RPNNode;

typedef struct stackList {
	RPNNode node;
	struct stackList* next;
} stackList;

typedef struct Stack {
	stackList* head;
	int size;
	void (*push)(struct Stack* stack, RPNNode node);
	RPNNode (*pop)(struct Stack* stack);
	RPNNode(*popHead) (struct Stack* stack);
	int (*empty)(const struct Stack stack);
	RPNNode (*top)(struct Stack stack);
	void (*print)(const struct Stack stack);
} Stack;

void push_Stack(Stack* stack, RPNNode node) {
	stackList* newNode = (stackList*)malloc(sizeof(stackList));
	if (newNode) {
		newNode->node = node;
		newNode->next = NULL;
		if (!stack->head) {
			stack->head = newNode;
			++(stack->size);
			return;
		}
		stackList* iter = stack->head;
		while (iter->next) iter = iter->next;
		iter->next = newNode;
		++(stack->size);
	}
}

RPNNode pop_Stack(Stack* stack) {
	if (!stack->head) return;
	RPNNode popped;
	if (!stack->head->next) {
		--(stack->size);
		popped = stack->head->node;
		free(stack->head);
		stack->head = NULL;
		return popped;
	}
	stackList* prev = stack->head;
	stackList* next = stack->head;
	while (next->next) {
		prev = next;
		next = next->next;
	}
	popped = next->node;
	prev->next = NULL;
	free(next);
	--(stack->size);
	return popped;
}

RPNNode pop_head_Stack(Stack* stack) {
	if (!stack->head) return;
	RPNNode popped;
	if (!stack->head->next) {
		popped = stack->head->node;
		free(stack->head);
		stack->head = NULL;
		--(stack->size);
		return popped;
	}
	stackList* head = stack->head;
	popped = head->node;
	stack->head = head->next;
	free(head);
	--(stack->size);
	return popped;
}

RPNNode top_Stack(const Stack stack) {
	if (!stack.head) return;
	stackList* iter = stack.head;
	while (iter->next) iter = iter->next;
	return iter->node;
}

void print_Stack(const Stack stack) {
	printf("Stack: ");
	stackList* iter = stack.head;
	while (iter) {
		if (iter->node.type == REAL_NUMBER) {
			printf("%lf ", iter->node.real_number);
		} 
		else if (iter->node.type == COMPLEX_NUMBER) {
			printf("%lfj ", iter->node.complex_number._Val[1]);
		}
		else if (iter->node.type == OPERATOR) {
			printf("%c ", iter->node.function);
		}
		else if (iter->node.type == FUNCTION) {
			printf("%d ", iter->node.function);
		}
		iter = iter->next;
	}
	printf("\n");
}

int empty_Stack(const Stack stack) {
	return stack.size > 0 ? 0 : 1;
}

void init_Stack(Stack* stack) {
	stack->head = NULL;
	stack->size = 0;
	stack->push = push_Stack;
	stack->pop = pop_Stack;
	stack->top = top_Stack;
	stack->print = print_Stack;
	stack->empty = empty_Stack;
	stack->popHead = pop_head_Stack;
}

#endif



